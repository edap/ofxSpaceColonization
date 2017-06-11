#include "ofxSpaceColonization.h"
// http://www.jgallant.com/procedurally-generating-trees-with-space-colonization-algorithm-in-xna/
ofxSpaceColonization::ofxSpaceColonization(){
    //auto rootPos = ofVec3f(0, 0, 0);
    //auto rootDir = ofVec3f(0, 1, 0);
    if(!use3d){
        root_position = ofVec3f(ofGetWidth()/2, ofGetHeight(), 0);
        root_direction = ofVec3f(0, -1, 0);
    }
    if (particles.empty()) {
        particles = generateDefaultParticles(400, use3d, trunk_length);
    }
    shared_ptr<ofxSpaceColonizationBranch> root(new ofxSpaceColonizationBranch(root_direction));
    root->move(ofVec3f(0,0,0), root_position);
    branches.push_back(root);

    for (auto vec:particles) {
        leaves.push_back(ofxSpaceColonizationLeaf(vec));
    }

    auto current = root;
    bool found = false;
    while(!found){
        ofVec3f cur = current->getPosition();
        for(auto l:leaves){
            float distance = cur.distance(l.getPosition());
            if(distance < max_dist){
                found = true;
            }
        }

        if (!found){
            shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(current->direction));
            if(!branches.empty()){
                int lastInsertedBranchId = branches.size() -1;
                nextBranch->setParentByIndex(lastInsertedBranchId);
                nextBranch->move((current->direction * branch_length ),
                                  branches.back()->getPosition());
            }
            addBranchToMesh(nextBranch);
            branches.push_back(nextBranch);
            current = branches.back();
        }
    }
}

void ofxSpaceColonization::build(){
    //TODO, prima setti tutte le variabili e poi chiami build

}

void ofxSpaceColonization::grow(){
    //arrivati verso la fine questo numero dovrebbe smettere di crescere
    // invece continua a salire

    if(!done_growing){
        //cout << branches.size() << endl;
        //process leaves
        for(int it=0;it<leaves.size();it++){
            float record = 10000.0;

            auto closestBranchIndex = -1;
            for(int i=0;i<branches.size();i++){
                auto distance = leaves[it].getPosition().distance(branches[i]->getPosition());
                auto vPos = branches[i]->getPosition();
                if(distance < min_dist){
                    leaves[it].reached = true;
                    closestBranchIndex = -1;
                    break;
                }else if (distance > max_dist){
                    //break;
                }else if ((closestBranchIndex < 0) || (distance < record)){
                    closestBranchIndex = i;
                    record = distance;
                }
            }

            //adjust direction and count
            if(closestBranchIndex>=0 && !leaves[it].reached){
                auto dir = (leaves[it].getPosition() - branches[closestBranchIndex]->getPosition()).normalize();

                auto vdir = (leaves[it].getPosition() - branches[closestBranchIndex]->getPosition()).normalize();
                // here you should add some random force to avoid the situation
                // where a branch is stucked between the attraction of 2 leaves
                // equidistant
                branches[closestBranchIndex]->direction = branches[closestBranchIndex]->direction + dir;
                branches[closestBranchIndex]->count = branches[closestBranchIndex]->count + 1;
            }

            if(leaves[it].reached){
                // in futuro, puoi tenere queste foglie, e disegnare solo quelle
                // che vengono reached
                leaves.erase(leaves.begin()+it);
            }
        }

        //Generate the new branches
        vector<shared_ptr<ofxSpaceColonizationBranch>> newBranches;
        for (int i = 0; i<branches.size(); i++) {
            if(branches[i]!= nullptr){
                if(branches[i]->count > 0){
                    //auto newDir = branches[i]->direction / (float(branches[i]->count));
                    auto newDir = branches[i]->direction / (float(branches[i]->count + 1));
                    shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(newDir));

                    nextBranch->setParentByIndex(i);
                    nextBranch->move(
                                      (newDir.normalize() * branch_length),
                                      branches[i]->getPosition());
                    addBranchToMesh(nextBranch);
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

void ofxSpaceColonization::setBranchLength(int _length){
    branch_length = _length;
};

void ofxSpaceColonization::draw(){
    for(auto l:leaves){
        l.draw();
    }

    for(int i = 0; i < branches.size(); i++){
        float lineWidth = ofMap(i, 0, branches.size(), 20, 1);
        ofSetLineWidth(lineWidth);
        //branches[i]->draw();
        auto parentIndex = branches[i]->indexParent;
        auto parentPos = branches[parentIndex]->getPosition();
        auto pos = branches[i]->getPosition();

        ofDrawLine(parentPos.x, parentPos.y,
                   parentPos.z, pos.x,
                   pos.y, pos.z);
    }
}

void ofxSpaceColonization::addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch){
    //TODO
}

vector<ofVec3f> ofxSpaceColonization::generateDefaultParticles(int n_particles, bool use3d, int _trunk_length) const{
    vector<ofVec3f> tmp_particles;
    int ray = 400;
    for(int i = 0; i< n_particles; i++){
        if(use3d){
            ofVec3f pos = ofVec3f(ofRandom(-ray,+ray),
                          ofRandom(_trunk_length, ray),
                          ofRandom(-ray,+ray));
            tmp_particles.push_back(pos);
        }else{
            ofVec3f pos = ofVec3f(ofRandom(0, ofGetWidth()),
                                  ofRandom((ofGetHeight()-trunk_length), 0),
                                  0);
            tmp_particles.push_back(pos);
        }

    }
    return tmp_particles;
}
