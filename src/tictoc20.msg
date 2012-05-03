//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


// 0 3 1
// 1 4 2
// 9 9 9


class ATransition extends cOwnedObject
{
    int currentState;
    int inStateTrigger;
    int outState;
};

message TicTocMsg20
{
    int hopCount = 0;
    int data;
    int mPathCon;
    ATransition t[3];
}


