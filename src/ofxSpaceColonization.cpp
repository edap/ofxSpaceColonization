#include "ofxSpaceColonization.h"
// http://www.jgallant.com/procedurally-generating-trees-with-space-colonization-algorithm-in-xna/
ofxSpaceColonization::ofxSpaceColonization(){
    auto rootPos = ofVec3f(ofGetWidth()/2, ofGetHeight(), 0);
    auto rootDir = ofVec3f(0, -1, 0);
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

            if(closestBranchIndex>=0 && !leaves[it].reached){
                auto dir = (leaves[it].getPosition() - branches[closestBranchIndex]->getPosition()).normalize();
                branches[closestBranchIndex]->direction = branches[closestBranchIndex]->direction + dir;
                branches[closestBranchIndex]->count = branches[closestBranchIndex]->count + 1;

                shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(dir));
                if(!branches.empty()){
                    nextBranch->setParent(branches.back());
                    nextBranch->move(branches[closestBranchIndex]->direction * branch_length);
                    addBranchToMesh(nextBranch);
                }
            }

            if(leaves[it].reached){
                // in futuro, puoi tenere queste foglie, e disegnare solo quelle
                // che vengono reached
                leaves.erase(leaves.begin()+it);
            }
        }

        for (int i = 0; i<branches.size(); i++) {
            if(branches[i]!= nullptr && branches[i]->count > 0){
                // controllare qui, shiffman dice di aggiungere 1 al count (min 44.52)
                auto newDir = branches[i]->direction / (float(branches[i]->count));
                //auto newDir = branches[i]->direction / (float(branches[i]->count + 1));
                shared_ptr<ofxSpaceColonizationBranch> nextBranch(new ofxSpaceColonizationBranch(newDir));
                nextBranch->setParent(branches[i]);
                nextBranch->move(newDir * branch_length);
                addBranchToMesh(nextBranch);
                //add nextBranch to mesh
                branches.push_back(nextBranch);
            }
            if(branches[i]!= nullptr){
                branches[i]->reset();
            }
        }
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
    for(auto b:branches){
        b->draw();
    }
}

void ofxSpaceColonization::addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch){
    //TODO
}
