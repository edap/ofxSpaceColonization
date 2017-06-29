// implementation of A. Runions, B. Lane & P. Prusinkiewicz / Modeling Trees with a Space Colonization Algorithm

#include "ofxSpaceColonization.h"


static const ofxSpaceColonizationOptions defaultSpaceColOptions = {
    150,                             // max_dist,
    10,                              // min_dist,
    150,                             // trunk_length
    glm::vec4(0.0f,0.0f,0.0f, 1.0f), // rootPosition
    glm::vec3(0.0f, 1.0f, 0.0f),     // rootDirection
    7,                               // branchLength
    false,                           // done growing
    false,                           // cap
    2.0,                             // radius;
    16,                              // resolution;
    1,                               // textureRepeat;
    0.9997                           // radiusScale;
};

ofxSpaceColonization::ofxSpaceColonization(){
    setup(defaultSpaceColOptions);
}

ofxSpaceColonization::ofxSpaceColonization(ofxSpaceColonizationOptions _opt){
    setup(_opt);
}

void ofxSpaceColonization::setup(ofxSpaceColonizationOptions _opt){
    this->options = _opt;
    this->setPosition(glm::vec3(_opt.rootPosition));
};

void ofxSpaceColonization::setLeavesPositions(vector<glm::vec3> _leaves_positions){
    this->leaves_positions = _leaves_positions;
};

void ofxSpaceColonization::build(){
    makeSureThatThereAreLeaves();
    glm::vec4 endPoint = glm::vec4(0.0f,1.0f,0.0f, 1.0);
    glm::quat orientation;
    shared_ptr<ofxSpaceColonizationBranch> root(new ofxSpaceColonizationBranch(options.rootPosition, endPoint, orientation, glm::vec3(0.0f, 1.0f, 0.0f), options.radius));
    branches.push_back(root);

    for (auto vec:this->leaves_positions) {
        leaves.push_back(ofxSpaceColonizationLeaf(vec));
    }

    auto current = root;
    bool found = false;
    // we build the trunk,adding a branch after another, until we do not reach the foliage

    while (!found) {
        glm::vec3 cur = glm::vec3(current->getEndPos());
        for (auto l:leaves) {
            float distance = glm::distance(cur, l.getPosition());
            if (distance < options.max_dist) {
                found = true;
            }
        }

        if (!found && !branches.empty()) {
            glm::vec3 parentDir = current->getEndDirection();
            glm::vec3 parentPos = glm::vec3(branches.back()->getEndPos());
            float parentRadius = branches.back()->getEndRadius();
            float newRadius = parentRadius * options.radiusScale;
            glm::quat parentOrientation = branches.back()->getEndOrientation();
            glm::vec3 newDir = parentDir;
            glm::vec3 newPos = parentPos + (newDir * options.branchLength);

            shared_ptr<ofxSpaceColonizationBranch> nextBranch(
                new ofxSpaceColonizationBranch(
                                               glm::vec4(parentPos, 1.0),
                                               glm::vec4(newPos, 1.0),
                                               parentOrientation,
                                               parentDir,
                                               newRadius)
            );
            int lastInsertedBranchId = branches.size() -1;
            nextBranch->setParentByIndex(lastInsertedBranchId);
            branches.push_back(nextBranch);
            current = branches.back();
            auto opt = ofxBranchCylinderOptions({
                options.cap,
                parentRadius,
                newRadius,
                options.resolution,
                options.textureRepeat });

            ofxBranchCylinder::putIntoMesh(nextBranch, this->getMesh(), opt);
        }
    }
}

void ofxSpaceColonization::grow(){
    grow(glm::vec3(0.0,0.0,0.0));
}

void ofxSpaceColonization::grow(glm::vec3 wind){
    float record = -1;
    if (!options.doneGrowing) {
        //If no leaves left, we are done
        if (leaves.size() == 0) {
            options.doneGrowing = true;
            return;
        }

        if(glm::length(wind) > 0){
            for (auto& l:leaves) {
                l.move(wind);
            }
        }

        //process leaves
        for (int it=0;it<leaves.size();it++) {
            //float record = 10000.0;
            //Find the nearest branch for this leaf
            auto closestBranchIndex = -1;

            for (int i=0;i<branches.size();i++) {
                auto distance = glm::distance(leaves[it].getPosition(),
                                              glm::vec3(branches[i]->getEndPos()));

                //options.min_dist is what in the paper it's called
                // "kill distance"
                if (distance < options.min_dist) {
                    leaves[it].setReached(true);
                    closestBranchIndex = -1;
                    break;
                } else if (distance > options.max_dist){
                    //break;
                } else if ((closestBranchIndex < 0) || (distance < record)){
                    closestBranchIndex = i;
                    record = distance;
                }
            }

            //adjust direction and count
            if (closestBranchIndex>=0 && !leaves[it].isReached()) {
                auto dir = leaves[it].getPosition() - (glm::vec3(branches[closestBranchIndex]->getEndPos()));
                auto dirNorm = glm::normalize(dir);
                // here you should add some random force to avoid the situation
                // where a branch is stucked between the attraction of 2 leaves
                // equidistant
                //glm::vec3 wind = glm::normalize(dir + glm::vec3(20.0,0.0, 0.0));
                branches[closestBranchIndex]->correctNextBranchDirection(dirNorm);
                branches[closestBranchIndex]->incrementCounterBy(1);
            }

            if (leaves[it].isReached()) {
                // TODO, maybe you can keep the leaves and draw just that one that get reached?
                leaves.erase(leaves.begin()+it);
            }
        }

        //Generate the new branches
        vector<shared_ptr<ofxSpaceColonizationBranch>> newBranches;
        for (int i = 0; i<branches.size(); i++) {
            if (branches[i] != nullptr) {
                if (branches[i]->getCount() > 0) {
                    glm::vec3 parentDir = branches[i]->getEndDirection();
                    glm::vec3 parentPos = glm::vec3(branches[i]->getEndPos());
                    float parentRadius = branches[i]->getEndRadius();
                    float newRadius = parentRadius * options.radiusScale;
                    glm::quat parentOrientation = branches[i]->getEndOrientation();
                    glm::vec3 nextBranchDir = branches[i]->getNextBranchDirectionDirection();
                    glm::vec3 newDir = glm::normalize(nextBranchDir / (float(branches[i]->getCount() + 1)));
                    glm::vec3 newPos = parentPos + (newDir * options.branchLength);

                    shared_ptr<ofxSpaceColonizationBranch> nextBranch(
                        new ofxSpaceColonizationBranch(glm::vec4(parentPos, 1.0),
                                                       glm::vec4(newPos, 1.0),
                                                       parentOrientation,
                                                       parentDir,
                                                       newRadius)
                    );
                    nextBranch->setParentByIndex(i);
                    auto opt = ofxBranchCylinderOptions({
                        options.cap,
                        parentRadius,
                        newRadius,
                        options.resolution,
                        options.textureRepeat });

                    ofxBranchCylinder::putIntoMesh(nextBranch, this->getMesh(), opt);
                    newBranches.push_back(nextBranch);
                }
                branches[i]->reset();
            }
        }
        branches.insert(branches.end(), newBranches.begin(), newBranches.end());
    }

}

vector<ofxSpaceColonizationLeaf> ofxSpaceColonization::getLeaves() const{
    return this->leaves;
}

void ofxSpaceColonization::makeSureThatThereAreLeaves(){
    if(leaves_positions.empty()){
        leaves_positions =
        ofxSpaceColonizationHelper::genRandomLeavesPositions(ofGetWidth(), ofGetHeight(), 400, defaultSpaceColOptions.trunk_length);
    }
}

void ofxSpaceColonization::clear(){
    options.doneGrowing = false;
    setup(options);
    leaves_positions.clear();
    leaves.clear();
    branches.clear();
    getMesh().clear();
};

