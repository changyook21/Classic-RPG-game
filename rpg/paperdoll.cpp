#include <iostream>

using namespace std;

#include "paperdoll.h"

Paperdoll::Paperdoll() {
    head = NULL;
    chest = NULL;
    gloves = NULL;
    back = NULL;
    pants = NULL;
    boots = NULL;
    rightHand = NULL;
    leftHand = NULL;
}

Paperdoll::Paperdoll(Paperdoll &other) {
    if (other.head == NULL) {
        head = NULL;
    }
    else {
        head = (Armor *)other.head->clone();
    }
    if (other.chest == NULL) {
        chest = NULL;
    }
    else {
        chest = (Armor *)other.chest->clone();
    }
    if (other.gloves == NULL) {
        gloves = NULL;
    }
    else {
        gloves = (Armor *)other.gloves->clone();
    }
    
    if (other.back == NULL) {
        back = NULL;
    }
    else {
        back = (Armor *)other.back->clone();
    }
    
    if (other.pants == NULL) {
        pants = NULL;
    }
    else {
        pants = (Armor *)other.pants->clone();
    }
    
    if (other.boots == NULL) {
        boots = NULL;
    }
    else {
        boots = (Armor *)other.boots->clone();
    }
    
    if (other.rightHand == NULL) {
        rightHand = NULL;
    }
    else {
        rightHand = (Weapon *)other.rightHand->clone();
    }
    
    if (other.leftHand == NULL) {
        leftHand = NULL;
    }
    else {
        leftHand = (Weapon *)other.leftHand->clone();
    }
}

void Paperdoll::print() const {
    cout << "[ 1:head(" << ((head==NULL)?' ':head->getShape())
    << ") 2:chest(" << ((chest==NULL)?' ':chest->getShape())
    << ") 3:gloves(" << ((gloves==NULL)?' ':gloves->getShape())
    << ") 4:back(" << ((back==NULL)?' ':back->getShape())
    << ") 5:pants(" << ((pants==NULL)?' ':pants->getShape())
    << ") 6:boots(" << ((boots==NULL)?' ':boots->getShape())
    << ") 7:rightHand(" << ((rightHand==NULL)?' ':rightHand->getShape())
    << ") 8:leftHand(" << ((leftHand==NULL)?' ':leftHand->getShape())
    << ") ]";
}

bool Paperdoll::equip(Item *item, Unit *unit) {
    // equipable has been passed
    if (item->isEquippable()) {
        if (item->isArmor()) {
            Armor *armor = (Armor *)item;
            int bodyPartNo = armor->getBodyPartID();
            if (bodyPartNo == BODY_PART_ID_HEAD) {
                if (head != NULL) {
                    return false;
                }
                else {
                    head = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
            else if (bodyPartNo == BODY_PART_ID_CHEST) {
                if (chest != NULL) {
                    return false;
                }
                else {
                    chest = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
            else if (bodyPartNo == BODY_PART_ID_HANDS) {
                if (gloves != NULL) {
                    return false;
                }
                else {
                    gloves = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
            else if (bodyPartNo == BODY_PART_ID_BACK) {
                if (back != NULL) {
                    return false;
                }
                else {
                    back = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
            else if (bodyPartNo == BODY_PART_ID_LEGS) {
                if (pants != NULL) {
                    return false;
                }
                else {
                    pants = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
            else if (bodyPartNo == BODY_PART_ID_FEET) {
                if (boots != NULL) {
                    return false;
                }
                else {
                    boots = armor;
                    unit->incDef(armor->getDef());
                    return true;
                }
            }
        }
        else if (item->isWeapon()) {
            Weapon *weapon = (Weapon *)item;
            int numHands = weapon->getNumHands();
            
            if (numHands == 2 && rightHand == NULL && leftHand == NULL) {
                rightHand = weapon;
                unit->incAtk(weapon->getAtk());
                return true;
            }
            else if (numHands == 1 && rightHand == NULL) {
                rightHand = weapon;
                unit->incAtk(weapon->getAtk());
                return true;
            }
            else if (numHands == 1 && leftHand == NULL && rightHand->getNumHands() < 2) {
                leftHand = weapon;
                unit->incAtk(weapon->getAtk());
                return true;
            }
            return false;
        }
        else {
            return false;
        }
    }
    // non-equipable has been passed
    return false;
}

Item *Paperdoll::unequip(int bodyPartNo, Unit *unit) {
    if (bodyPartNo == BODY_PART_ID_HEAD) {
        if (head != NULL) {
            Item *itemToReturn = head;
            unit->decDef(head->getDef());
            head = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_CHEST) {
        if (chest != NULL) {
            Item *itemToReturn = chest;
            unit->decDef(chest->getDef());
            chest = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_HANDS) {
        if (gloves != NULL) {
            Item *itemToReturn = gloves;
            unit->decDef(gloves->getDef());
            gloves = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_BACK) {
        if (back != NULL) {
            Item *itemToReturn = back;
            unit->decDef(back->getDef());
            back = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_LEGS) {
        if (pants != NULL) {
            Item *itemToReturn = pants;
            unit->decDef(pants->getDef());
            pants = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_FEET) {
        if (boots != NULL) {
            Item *itemToReturn = boots;
            unit->decDef(boots->getDef());
            boots = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_RIGHT_HAND) {
        if (rightHand != NULL) {
            Item *itemToReturn = rightHand;
            unit->decAtk(rightHand->getAtk());
            rightHand = NULL;
            
            if (((Weapon *)itemToReturn)->getNumHands() == WEAPON_ONE_HAND) {
                rightHand = leftHand;
                leftHand = NULL;
            }
            
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    else if (bodyPartNo == BODY_PART_ID_LEFT_HAND) {
        if (leftHand != NULL) {
            Item *itemToReturn = leftHand;
            unit->decAtk(leftHand->getAtk());
            leftHand = NULL;
            return itemToReturn;
        }
        else {
            return NULL;
        }
    }
    return NULL;
}

Weapon *Paperdoll::getRightHand() const {
    return rightHand;
}

Weapon *Paperdoll::getLeftHand() const {
    return leftHand;
}

void Paperdoll::save(ostream &out) const {
    out << "#-------------------- class Paperdoll" << endl;
    
    if (head == NULL) {
        out << "#======================================== head" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== head" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << head->getID() << endl;
        head->save(out);
    }
    
    if (chest == NULL) {
        out << "#======================================== chest" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== chest" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << chest->getID() << endl;
        chest->save(out);
    }

    if (gloves == NULL) {
        out << "#======================================== gloves" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== gloves" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << gloves->getID() << endl;
        gloves->save(out);
    }

    if (back == NULL) {
        out << "#======================================== back" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== back" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << back->getID() << endl;
        back->save(out);
    }

    if (pants == NULL) {
        out << "#======================================== pants" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== pants" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << pants->getID() << endl;
        pants->save(out);
    }

    if (boots == NULL) {
        out << "#======================================== boots" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== boots" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << boots->getID() << endl;
        boots->save(out);
    }

    if (rightHand == NULL) {
        out << "#======================================== rightHand" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== rightHand" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << rightHand->getID() << endl;
        rightHand->save(out);
    }

    if (leftHand == NULL) {
        out << "#======================================== leftHand" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== leftHand" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << leftHand->getID() << endl;
        leftHand->save(out);
    }
}

void Paperdoll::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Paperdoll" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "#======================================== head" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        head = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << head->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        head = (Armor *)createItemByID(itemID); // call factory
        head->load(in);
    }
    
    //out << "#======================================== chest" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        chest = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << chest->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        chest = (Armor *)createItemByID(itemID); // call factory
        chest->load(in);
    }
    
    //out << "#======================================== gloves" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        gloves = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << gloves->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        gloves = (Armor *)createItemByID(itemID); // call factory
        gloves->load(in);
    }

    //out << "#======================================== back" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        back = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << back->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        back = (Armor *)createItemByID(itemID); // call factory
        back->load(in);
    }

    //out << "#======================================== pants" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        pants = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << pants->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        pants = (Armor *)createItemByID(itemID); // call factory
        pants->load(in);
    }

    //out << "#======================================== boots" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        boots = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << boots->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        boots = (Armor *)createItemByID(itemID); // call factory
        boots->load(in);
    }

    //out << "#======================================== rightHand" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        rightHand = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << rightHand->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        rightHand = (Weapon *)createItemByID(itemID); // call factory
        rightHand->load(in);
    }

    //out << "#======================================== leftHand" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        leftHand = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << leftHand->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        leftHand = (Weapon *)createItemByID(itemID); // call factory
        leftHand->load(in);
    }
}
