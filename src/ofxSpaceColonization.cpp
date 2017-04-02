#include "ofxSpaceColonization.h"
// http://www.jgallant.com/procedurally-generating-trees-with-space-colonization-algorithm-in-xna/
ofxSpaceColonization::ofxSpaceColonization(){
    auto rootPos = ofVec3f(0, 0, 0);
    auto rootDir = ofVec3f(0, 1, 0);
    shared_ptr<ofxSpaceColonizationBranch> root(new ofxSpaceColonizationBranch(rootDir));
    root->move(rootPos);
    branches.push_back(root);

    for (int i =0; i<n_leaves; i++) {
        leaves.push_back(ofxSpaceColonizationLeaf());
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
                nextBranch->setParent(branches.back());
                nextBranch->move(current->direction * branch_length );
            }
            addBranchToMesh(nextBranch);
            branches.push_back(nextBranch);
            current = branches.back();
        }
    }
}

void ofxSpaceColonization::grow(){
    //arrivati verso la fine questo numero dovrebbe smettere di crescere
    // invece continua a salire

    if(!done_growing){
        cout << branches.size() << endl;
        //process leaves
        for(int it=0;it<leaves.size();it++){
            float record = 10000.0;

            auto closestBranchIndex = -1;
            for(int i=0;i<branches.size();i++){
                auto distance = leaves[it].getPosition().distance(branches[i]->getPosition());
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
                    // controllare qui, shiffman dice di aggiungere 1 al count (min 44.52)
                    auto newDir = branches[i]->direction / (float(branches[i]->count));
                    //auto newDir = branches[i]->direction / (float(branches[i]->count + 1));
                    shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(newDir));
                    nextBranch->setParent(branches[i]);
                    nextBranch->move(newDir.normalize() * branch_length);
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
        branches[i]->draw();
    }
}

void ofxSpaceColonization::addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch){
    //TODO
}
