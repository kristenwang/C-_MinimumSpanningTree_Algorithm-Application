//
//  main.cpp
//  Get minimal spanning tree based on created graph
//
//  Created by Chuyang Wang on 14-7-14.
//  Copyright (c) 2014 Chuyang Wang. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INFINITY 9999
#define max_name 50
#define max_dot_num 50

typedef char dots[max_name];
typedef int adjMatrix[max_dot_num][max_dot_num];

typedef struct {
    dots adjvex;
    int lowcost;
}close[max_dot_num];

typedef struct{
    dots vexs[max_dot_num];
    adjMatrix arcs;
    int dotnum;
}PrimGraph;
//Locate function，locate point position，if there is point in the graph
int Locate(PrimGraph P,dots u){
    int i;
    if (P.dotnum != -1) {
        for(i = 0; i < P.dotnum; i++)
            if(strcmp(u,P.vexs[i]) == 0)
                return i;
        return -1;
        
    }else{
        return -2;
    }
}
//Create graph，including record point number，name，and create its Adjacency matrix
void CreatGrapgh(PrimGraph &P){
    int i, j, k, w;
    dots v1, v2, v3;
    P.dotnum = -1;
    
    printf("Please input dot number： ");
    scanf("%d", &P.dotnum);
    if (P.dotnum<=0||P.dotnum>=50) {
        scanf("%s", v3);
        printf("Wrong Input!\n");
        CreatGrapgh(P);
    }
    else if(P.dotnum>0&&P.dotnum<=2){
        printf("Please input number greater than 2！\n");
        CreatGrapgh(P);
    }else if (P.dotnum>2){
    
    printf("Please input dot names： \n");
    for(i = 0; i < P.dotnum; ++i)
        scanf("%s",P.vexs[i]);
    for(i = 0; i < P.dotnum; ++i)
        for (j = 0; j < P.dotnum; ++j) {
            P.arcs[i][j] = INFINITY;
        }
    
    int m = (P.dotnum * (P.dotnum - 1)) / 2;
    for(k = 0; k < m; ++k) {
        printf("Input two vertexs and length：");
        scanf("%s %s %d", v1, v2, &w);
        if (strcmp(v1,"?") != 0||strcmp(v2,"?") != 0) {
            i = Locate(P, v1);
            j = Locate(P, v2);
            P.arcs[i][j] = P.arcs[j][i] = w;
        }
        else if (strcmp(v1,"?") == 0||strcmp(v2,"?") == 0)
            break;
    }
        printf("Graph is created！\n");
    }
}
//Minimum distance function，return point with minimum distance
int minimum(close c, PrimGraph P){
    int i, k, min;
    min = INFINITY;
    k = -1;
    for (i = 0; i <= P.dotnum; i++)
        if (c[i].lowcost < min && c[i].lowcost > 0) {
            min = c[i].lowcost;
            k = i;
        }
    return k;
}
//Create and show minimal spanning tree
void Prim(PrimGraph P,dots u){
    int i, j, k = 0;
    int flag[1000];                        // Use flag to record which point has been accessed
    int count = 1;                         // Use countto record how many points have been accessed
    int length = 0;                        // Use length to record the length of minimum path
    close closedge;
    bool isbreak = false;
    flag[0] = 0;
    
    //Get first two points and length to linked points, and store them in arrays
    k = Locate(P, u);
    for (j = 0; j <= P.dotnum; ++j) {
        if(j != k)
            closedge[k].lowcost = 0;
        strcpy(closedge[j].adjvex, u);
        closedge[j].lowcost = P.arcs[k][j];
    }
    
    printf("Vertexs and length：：\n");
    for (i = 1; i < P.dotnum; ++i) {
        k = minimum(closedge,P);          //Minimum distance points
        if (k == -1) {                    //If not, break loop
            isbreak = true;
            break;
        }
        
        length = length + P.arcs[k][Locate(P, closedge[k].adjvex)];
        printf("%s-(%d)->%s\n",closedge[k].adjvex, P.arcs[k][Locate(P, closedge[k].adjvex)], P.vexs[k]);
        closedge[k].lowcost = 0;
        flag[count] = k;                  //Mark dot with minimum distance as accessed
        count++;
        
        for (j = 0; j < P.dotnum; ++j)
            if (P.arcs[k][j] < closedge[j].lowcost) {
                strcpy(closedge[j].adjvex, P.vexs[k]);
                closedge[j].lowcost = P.arcs[k][j];
            }
    }
    
    if(isbreak){
        printf("Cannot generate minimal spanning tree!\n Accessed Points：\n");
        for(i = 0; i < count; i++){
            printf("%s ",P.vexs[flag[i]]);
        }
        printf("\n");
    }
    printf("The length of is minimal spanning tree%d \n",length);
}
//Create and show minimal spanning tree
void Build(PrimGraph P){
    int a = 0;
    dots sp;
    if (P.dotnum != -1) {
        printf("Please input start point：");
        scanf("%s",sp);
        a = Locate(P, sp);
        if (a >= 0) {  
            Prim(P, P.vexs[a]);
        }
        else if (a == -1){         
            printf("Wrong Input！\n");
            Build(P);
        }
    }
    else if (P.dotnum == -1){           
        printf("No Graph Yet！！\n");
    }
}
//Show Help
void Help(){
    printf("=======================================================\n");
    printf("**           A.Create graph                          **\n");
    printf("**           B.Create and show minimal spanning tree **\n");
    printf("**           C.Exit                                  **\n");
    printf("**           D.Help                                  **\n");
    printf("=======================================================\n");
}
// Input Command
void Choose(PrimGraph P){
    dots c;
    printf("\n");
    printf("Please choose operation：");
    scanf("%s",c);
    if (strcmp(c, "A") == 0) {
        CreatGrapgh(P); 
    }
    else if (strcmp(c, "B") == 0){
        Build(P);                     
    }
    else if (strcmp(c, "C") == 0){
        exit(0);                          
    }
    else if (strcmp(c, "D") == 0){
        Help();                      
    }
    else{
        printf("Wrong Input! \n");        
    }
    Choose(P);                                            //recursion
}
// Main
int main(){
    PrimGraph P;
    printf("**            Minimal Spanning Tree based on Created Graph            **\n");
    printf("**Please create graph first before creating and show minimal spanning tree**\n");
    Help();
    P.dotnum = -1;                                    
    Choose(P);
    return NULL;
}


