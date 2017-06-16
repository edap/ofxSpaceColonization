#include "ofxSpaceColonization.h"
// http://www.jgallant.com/procedurally-generating-trees-with-space-colonization-algorithm-in-xna/
ofxSpaceColonization::ofxSpaceColonization(){
}

void ofxSpaceColonization::build(){
    if (use2d) {
        root_position = glm::vec3(ofGetWidth()/2, ofGetHeight(), 0);
        root_direction = glm::vec3(0.0f, -1.0f, 0.0f);
    }
    if (leaves_positions.empty()) {
        leaves_positions = ofxSpaceColonizationHelper::genRandomLeavesPositions(ofGetWidth(), ofGetHeight(), 400, use2d, trunk_length);
    }
    shared_ptr<ofxSpaceColonizationBranch> root(new ofxSpaceColonizationBranch(root_direction));
    root->move(glm::vec3(0.0f,0.0f,0.0f) + root_position);
    branches.push_back(root);

    for (auto vec:leaves_positions) {
        leaves.push_back(ofxSpaceColonizationLeaf(vec));
    }

    auto current = root;
    bool found = false;
    // we build the trunk,adding a branch after another, until we do not reach the foliage
    while (!found) {
        glm::vec3 cur = current->getPosition();
        for (auto l:leaves) {
            float distance = glm::distance(cur, l.getPosition());
            if (distance < max_dist) {
                found = true;
            }
        }

        if (!found && !branches.empty()) {
            glm::vec3 parentDir = current->getDirection();
            glm::vec3 parentPos = branches.back()->getPosition();
            glm::vec3 newDir = parentDir;
            glm::vec3 newPos = parentPos + (newDir * branch_length);

            shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(parentDir));
            int lastInsertedBranchId = branches.size() -1;
            nextBranch->setParentByIndex(lastInsertedBranchId);
            nextBranch->move(newPos);

            branches.push_back(nextBranch);
            current = branches.back();
            addBranchToMesh(glm::vec4(parentPos,1.0), glm::vec4(newPos,1.0), parentDir, newDir);
        }
    }
}

void ofxSpaceColonization::grow(){
    float record = -1;
    cout << "size" << endl;
    cout << leaves.size() << endl;
    if (!done_growing) {
        //If no leaves left, we are done
        if (leaves.size() == 0) {
            done_growing = true;
            return;
        }
        cout << branches.size() << endl;
        //process leaves
        for (int it=0;it<leaves.size();it++) {
            //float record = 10000.0;
            //Find the nearest branch for this leaf
            auto closestBranchIndex = -1;
            for (int i=0;i<branches.size();i++) {
                auto distance = glm::distance(leaves[it].getPosition(), branches[i]->getPosition());
                if (distance < min_dist) {
                    leaves[it].setReached(true);
                    closestBranchIndex = -1;
                    break;
                } else if (distance > max_dist){
                    //break;
                } else if ((closestBranchIndex < 0) || (distance < record)){
                    closestBranchIndex = i;
                    record = distance;
                }
            }

            //adjust direction and count
            if (closestBranchIndex>=0 && !leaves[it].isReached()) {
                auto dir = leaves[it].getPosition() - (branches[closestBranchIndex]->getPosition());
                auto dirNorm = glm::normalize(dir);
                cout << "counter" << endl;

                // here you should add some random force to avoid the situation
                // where a branch is stucked between the attraction of 2 leaves
                // equidistant
                branches[closestBranchIndex]->addToDirection(dirNorm);
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
                    glm::vec3 parentDir = branches[i]->getDirection();
                    glm::vec3 oldDir = branches[i]->getOldDirection();
                    glm::vec3 parentPos = branches[i]->getPosition();
                    glm::vec3 newDir = glm::normalize(parentDir / (float(branches[i]->getCount() + 1)));
                    glm::vec3 newPos = parentPos + (newDir * branch_length);

                    shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(newDir));
                    nextBranch->setParentByIndex(i);
                    nextBranch->move(newPos);

                    addBranchToMesh(glm::vec4(parentPos,1.0), glm::vec4(newPos,1.0), oldDir,newDir);
                    newBranches.push_back(nextBranch);
                }
                branches[i]->reset();
            }
        }
        branches.insert(branches.end(), newBranches.begin(), newBranches.end());
    }

}


void ofxSpaceColonization::setMinDist(int _min_dist){
    min_dist = _min_dist;
};

void ofxSpaceColonization::setMaxDist(int _max_dist){
    max_dist = _max_dist;
};

void ofxSpaceColonization::set2d(bool _val){
    this->use2d = _val;
};

void ofxSpaceColonization::setBranchLength(int _length){
    branch_length = _length;
};

void ofxSpaceColonization::setTrunkLength(int _length){
    trunk_length = _length;
};

glm::vec3 ofxSpaceColonization::getBranchPosition(int _index) const {
    return this->branches[_index]->getPosition();
};

glm::vec3 ofxSpaceColonization::getParentBranchPosition(int _index) const {
    auto parentIndex = this->branches[_index]->getIndexParent();
    return this->branches[parentIndex]->getPosition();
};

//template <class ofxSpaceColonizationGeom>void ofxSpaceColonization::addBranchToMesh(ofxSpaceColonizationGeom geom){
//    //TODO
//}

//TODO this method has to go out from this class, leave the alg
// alone
void ofxSpaceColonization::addBranchToMesh(glm::vec4 posStart, glm::vec4 posEnd,
                                           glm::vec3 startDir, glm::vec3 endDir){
    if (!use2d) {
        auto branchMesh = ofxSpaceColonizationTu(posStart, posEnd, startDir, endDir, this->mesh);
    }
}

void ofxSpaceColonization::draw3d(){
    this->mesh.draw();
}

void ofxSpaceColonization::drawWireframe(){
    this->mesh.drawWireframe();
}

vector<ofxSpaceColonizationLeaf> ofxSpaceColonization::getLeaves() const{
    return this->leaves;
}

int ofxSpaceColonization::getSizeBranches() const{
    return this->branches.size();
}

