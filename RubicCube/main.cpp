#define GL_SILENCE_DEPRECATION
#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;
//-------------------------------------------------------------------------------------------
//number of vertices is 288, 8 mini cubes
point4 pointsCube[9][288];
color4 colorsCube[9][288];

//8 cubes
point4 cube_zero[8];
point4 cube_one[8];
point4 cube_two[8];
point4 cube_three[8];
point4 cube_four[8];
point4 cube_five[8];
point4 cube_six[8];
point4 cube_seven[8];
point4 rubic_cube[8][8];

//6 faces
int right_face[4];
int left_face[4];
int bottom_face[4];
int top_face[4];
int back_face[4];
int front_face[4];
int random_counter=0;
//int solver_counter=5;
bool start = true;

// RGBA olors
color4 vertex_colors[6] = {
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.5, 0.0, 1.0 )  // orange
    
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;
//----------------------------------------------------------------------------

//initialize points for 8 cubes
void
initCubePoints()
{
    cube_zero[0]=point4(-0.3,0.3,0.3,1.0);
    cube_zero[1]=point4(-0.3,0.0,0.3,1.0);
    cube_zero[2]=point4(0.0,0.0,0.3,1.0);
    cube_zero[3]=point4(0.0,0.3,0.3,1.0);
    cube_zero[4]=point4(-0.3,0.3,0.0,1.0);
    cube_zero[5]=point4(-0.3,0.0,0.0,1.0);
    cube_zero[6]=point4(0.0,0.0,0.0,1.0);
    cube_zero[7]=point4(0.0,0.3,0.0,1.0);
    
    cube_one[0]= point4(-0.3,0.3,0.0,1.0);
    cube_one[1]= point4(-0.3,0.0,0.0,1.0);
    cube_one[2]= point4(0.0,0.0,0.0,1.0);
    cube_one[3]=point4(0.0,0.3,0.0,1.0);
    cube_one[4]=point4(-0.3,0.3,-0.3,1.0);
    cube_one[5]= point4(-0.3,0.0,-0.3,1.0);
    cube_one[6]=point4(0.0,0.0,-0.3,1.0);
    cube_one[7]= point4(0.0,0.3,-0.3,1.0);
    
    cube_two[0]=point4(0.0,0.3,0.0,1.0);
    cube_two[1]=point4(0.0,0.0,0.0,1.0);
    cube_two[2]=point4(0.3,0.0,0.0,1.0);
    cube_two[3]=point4(0.3,0.3,0.0,1.0);
    cube_two[4]=point4(0.0,0.3,-0.3,1.0);
    cube_two[5]=point4(0.0,0.0,-0.3,1.0);
    cube_two[6]=point4(0.3,0.0,-0.3,1.0);
    cube_two[7]=point4(0.3,0.3,-0.3,1.0);
    
    cube_three[0]=point4(0.0,0.3,0.3,1.0);
    cube_three[1]=point4(0.0,0.0,0.3,1.0);
    cube_three[2]=point4(0.3,0.0,0.3,1.0);
    cube_three[3]=point4(0.3,0.3,0.3,1.0);
    cube_three[4]=point4(0.0,0.3,0.0,1.0);
    cube_three[5]=point4(0.0,0.0,0.0,1.0);
    cube_three[6]=point4(0.3,0.0,0.0,1.0);
    cube_three[7]=point4(0.3,0.3,0.0,1.0);
    
    cube_four[0]= point4(-0.3,0.0,0.3,1.0);
    cube_four[1]=point4(-0.3,-0.3,0.3,1.0);
    cube_four[2]= point4(0.0,-0.3,0.3,1.0);
    cube_four[3]=point4(0.0,0.0,0.3,1.0);
    cube_four[4]=point4(-0.3,0.0,0.0,1.0);
    cube_four[5]= point4(-0.3,-0.3,0.0,1.0);
    cube_four[6]=point4(0.0,-0.3,0.0,1.0);
    cube_four[7]=point4(0.0,0.0,0.0,1.0);
    
    cube_five[0]=point4(-0.3,0.0,0.0,1.0);
    cube_five[1]=point4(-0.3,-0.3,0.0,1.0);
    cube_five[2]=point4(0.0,-0.3,0.0,1.0);
    cube_five[3]=point4(0.0,0.0,0.0,1.0);
    cube_five[4]=point4(-0.3,0.0,-0.3,1.0);
    cube_five[5]=point4(-0.3,-0.3,-0.3,1.0);
    cube_five[6]=point4(0.0,-0.3,-0.3,1.0);
    cube_five[7]=point4(0.0,0.0,-0.3,1.0);
    
    cube_six[0]=point4(0.0,0.0,0.0,1.0);
    cube_six[1]=point4(0.0,-0.3,0.0,1.0);
    cube_six[2]=point4(0.3,-0.3,0.0,1.0);
    cube_six[3]=point4(0.3,0.0,0.0,1.0);
    cube_six[4]=point4(0.0,0.0,-0.3,1.0);
    cube_six[5]=point4(0.0,-0.3,-0.3,1.0);
    cube_six[6]=point4(0.3,-0.3,-0.3,1.0);
    cube_six[7]=point4(0.3,0.0,-0.3,1.0);
    
    cube_seven[0]=point4(0.0,0.0,0.3,1.0);
    cube_seven[1]=point4(0.0,-0.3,0.3,1.0);
    cube_seven[2]=point4(0.3,-0.3,0.3,1.0);
    cube_seven[3]=point4(0.3,0.0,0.3,1.0);
    cube_seven[4]=point4(0.0,0.0,0.0,1.0);
    cube_seven[5]=point4(0.0,-0.3,0.0,1.0);
    cube_seven[6]=point4(0.3,-0.3,0.0,1.0);
    cube_seven[7]=point4(0.3,0.0,0.0,1.0);
    
    for (int i=0; i<8; i++) {
        rubic_cube[0][i]=cube_zero[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[1][i]=cube_one[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[2][i]=cube_two[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[3][i]=cube_three[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[4][i]=cube_four[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[5][i]=cube_five[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[6][i]=cube_six[i];
    }
    
    for (int i=0; i<8; i++) {
        rubic_cube[7][i]=cube_seven[i];
    }
}


//initialize faces
void
initFaces()
{
    for (int i=0; i<4; i++) {
        top_face[i]=i;    }
    
    for (int i=0; i<4; i++) {
        bottom_face[i]=i+4;    }
    
    front_face[0] = 4;
    front_face[1] = 0;
    front_face[2] = 3;
    front_face[3] = 7;
    
    back_face[0] = 6;
    back_face[1] = 2;
    back_face[2] = 1;
    back_face[3] = 5;
    
    right_face[0] = 7;
    right_face[1] = 3;
    right_face[2] = 2;
    right_face[3] = 6;
    
    left_face[0] = 5;
    left_face[1] = 1;
    left_face[2] = 0;
    left_face[3] = 4;
}

int Index = 0;

void
quad( int a, int b, int c, int d, int cube, int color )
{
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][a]; Index++;
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][b]; Index++;
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][c]; Index++;
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][a]; Index++;
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][c]; Index++;
    colorsCube[cube][Index] = vertex_colors[color]; pointsCube[cube][Index]=rubic_cube[cube][d]; Index++;
    
    if(Index==36){
        Index=0;
    }
}
//----------------------------------------------------------------------------
// generate 12 triangles 
void
rubicCube()
{
    
    quad( 0, 1, 2, 3, 0, 0 );quad( 3, 2, 6, 7, 0, 1);quad( 7, 6, 5, 4, 0, 2);
    quad( 4, 5, 1, 0, 0, 3 );quad( 4, 0, 3, 7, 0, 4);quad( 5, 1, 2, 6, 0, 5);
    
    quad( 0, 1, 2, 3, 1, 0);quad( 3, 2, 6, 7, 1, 1);quad( 7, 6, 5, 4, 1, 2);
    quad( 4, 5, 1, 0, 1, 3);quad( 4, 0, 3, 7, 1, 4);quad( 5, 1, 2, 6, 1, 5);
    
    quad( 0, 1, 2, 3, 2, 0);quad( 3, 2, 6, 7, 2, 1);quad( 7, 6, 5, 4, 2, 2);
    quad( 4, 5, 1, 0, 2, 3);quad( 4, 0, 3, 7, 2, 4);quad( 5, 1, 2, 6, 2, 5);
    
    quad( 0, 1, 2, 3, 3, 0);quad( 3, 2, 6, 7, 3, 1);quad( 7, 6, 5, 4, 3, 2);
    quad( 4, 5, 1, 0, 3, 3);quad( 4, 0, 3, 7, 3, 4);quad( 5, 1, 2, 6, 3, 5);
    
    quad( 0, 1, 2, 3, 4, 0);quad( 3, 2, 6, 7, 4, 1);quad( 7, 6, 5, 4, 4, 2);
    quad( 4, 5, 1, 0, 4, 3);quad( 4, 0, 3, 7, 4, 4);quad( 5, 1, 2, 6, 4, 5);
    
    quad( 0, 1, 2, 3, 5, 0);quad( 3, 2, 6, 7, 5, 1);quad( 7, 6, 5, 4, 5, 2);
    quad( 4, 5, 1, 0, 5, 3);quad( 4, 0, 3, 7, 5, 4);quad( 5, 1, 2, 6, 5, 5);
    
    quad( 0, 1, 2, 3, 6, 0);quad( 3, 2, 6, 7, 6, 1);quad( 7, 6, 5, 4, 6, 2);
    quad( 4, 5, 1, 0, 6, 3);quad( 4, 0, 3, 7, 6, 4);quad( 5, 1, 2, 6, 6, 5);
    
    quad( 0, 1, 2, 3, 7, 0);quad( 3, 2, 6, 7, 7, 1);quad( 7, 6, 5, 4, 7, 2);
    quad( 4, 5, 1, 0, 7, 3);quad( 4, 0, 3, 7, 7, 4);quad( 5, 1, 2, 6, 7, 5);
    
    
    int ind=0;
    for(int i=0; i<8; i++){
        for(int k=0; k<36; k++){
            pointsCube[8][ind]=pointsCube[i][k];
            colorsCube[8][ind]=colorsCube[i][k];
            ind+=1;
        }
    }
}

//--------------------------------------------------------------------------
//boolean helpers to rotate
bool topFaceClockwise = false; bool topFaceCounterClockwise = false;
bool rightFaceClockwise = false; bool rightFaceCounterClockwise = false;
bool frontFaceClockwise = false; bool frontFaceCounterClockwise = false;
bool turn_up= false; bool turn_down = false; bool turn_right = false; bool turn_left = false;

//randomization boolean
bool randomize = false;
//bool solver = false;
//----------------------------------------------------------------------------

//9 vao and 9 modelview (8 cube + 1 rubic cube)
GLuint  ModelView, Projection;
GLuint vao[9];
GLuint vPosition;
GLuint vColor;
mat4 model_view[9];

void init()
{
    initCubePoints();
    initFaces();
    rubicCube();
    
    GLuint buffer;
    // Create vertex array objects
    glGenVertexArrays( 9, vao );
    // Load shaders and use the resulting shader program
    GLuint program=InitShader( "vshader.glsl", "fshader.glsl" );
    
    for(int i=0; i<9; i++){
        glBindVertexArray( vao[i] );
        glGenBuffers( 1, &buffer );
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        glBufferData( GL_ARRAY_BUFFER, sizeof(pointsCube[i]) + sizeof(colorsCube[i]), NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(pointsCube[i]), pointsCube[i] );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(pointsCube[i]), sizeof(colorsCube[i]), colorsCube[i] );
        
        vPosition = glGetAttribLocation( program, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        
        vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(pointsCube[i])) );
        model_view[i] = identity();
    }
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Set current program object
    glUseProgram( program );
    
    // Enable hidden surface removal
    glEnable( GL_DEPTH_TEST );
    
    // Set state variable "clear color" to clear buffer with.
    //black background
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

//----------------------------------------------------------------------------
//display function
//check each rotation and display accordingly


void
display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0; i<8 ;i++){
        glBindVertexArray(vao[i]);
        //-----------------------
        if(rightFaceClockwise){
            if(i==right_face[3]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[2]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[1]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[0]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(rightFaceCounterClockwise){
            if(i==right_face[3]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[2]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[1]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==right_face[0]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateX(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(topFaceClockwise){
            if(i==top_face[3]) {
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[2]) {
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[1]) {
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[0]) {
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(topFaceCounterClockwise){
            if(i==top_face[3]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[2]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[1]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==top_face[0]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(frontFaceClockwise) {
            if(i==front_face[3]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==front_face[2]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }  else if (i==front_face[1]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }  else if (i==front_face[0]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(frontFaceCounterClockwise){
            if(i==front_face[3]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==front_face[2]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==front_face[1]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            } else if (i==front_face[0]){
                model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateZ(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
            }
        }
        
         if(turn_down){
            model_view[i] =  RotateX(-1.0) *  model_view[i];
        }
         if(turn_up){
            model_view[i] = RotateX(1.0) *  model_view[i];
        }
         if(turn_right){
            model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(-1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
        }
         if(turn_left){
            model_view[i]= RotateX(45.0) * RotateY(-45.0) * RotateY(1.0)* RotateY(45.0) * RotateX(-45.0) *  model_view[i];
        }
        //-----------------------
        
         if(start){ //initial looking of the cube used only at the beginning then it is set false
            model_view[i] =RotateX( 45.0 ) * RotateY( -45.0) * RotateZ(0.0) * model_view[i];
            
        }
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view[i] );
        glDrawArrays( GL_TRIANGLES, 0, 288 );
        
    }
    
    start=false;
    glutSwapBuffers();
    
}

//---------------------------------------------------------------------
// reshape
void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    // Set projection matrix
    mat4  projection;
    if (w <= h)
        projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
                           1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
    else  projection = Ortho(-1.0* (GLfloat) w / (GLfloat) h, 1.0 *
                             (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

//rotating each face
//total 6 functions
//3 clockwise & 3 counterclockwise
//updating each face

void
rotateOneFace(){
    
    int temp_right[4]; int temp_left[4]; int temp_top[4]; int temp_bottom[4]; int temp_front[4]; int temp_back[4];
    
    for (int i = 0; i<4; i++) {
        temp_right[i] = right_face[i]; temp_bottom[i] = bottom_face[i];
        temp_left[i] = left_face[i]; temp_top[i] = top_face[i];
        temp_front[i] = front_face[i]; temp_back[i] = back_face[i];
    }
    
    if(topFaceClockwise ){
        for (int i=0; i<4; i++) {
            top_face[i] = temp_top[(i+1)%4];
        }
        for (int i=1; i<3; i++) {
            left_face[i] = temp_back[i];
            right_face[i]= temp_front[i];
            front_face[i] = temp_left[i];
            back_face[i] = temp_right[i];
        }
    }
    
    if(topFaceCounterClockwise ){
        
        for (int i=0; i<4; i++) {
            top_face[i] = temp_top[(i+3)%4];
        }
        
        for (int i=1; i<3; i++) {
            left_face[i] = temp_front[i];
            right_face[i] = temp_back[i];
            front_face[i] = temp_right[i];
            back_face[i] = temp_left[i];
        }
    }
    
    if(rightFaceClockwise ){
        for (int i=0; i<4; i++) {
            right_face[i] = temp_right[(i+1)%4];
        }
        for (int i=2; i<4; i++) {
        front_face[i] = temp_top[i];
        }
        
        back_face[0] = temp_bottom[3];
        back_face[1] = temp_bottom[2];
        
        top_face[2] = temp_back[0];
        top_face[3] = temp_back[1];
        
        bottom_face[2] = temp_front[3];
        bottom_face[3] = temp_front[2];
    }
    
    if(rightFaceCounterClockwise){
        for (int i=0; i<4; i++) {
            right_face[i] = temp_right[(i+3)%4];
        }
        
        front_face[2] = temp_bottom[3];
        front_face[3] = temp_bottom[2];
        
        back_face[0] = temp_top[2];
        back_face[1] = temp_top[3];
        
        for (int i=2; i<4; i++) {
        top_face[i] = temp_front[i];
        }
        
        bottom_face[2] = temp_back[1];
        bottom_face[3] = temp_back[0];
        
    }
    
    if(frontFaceClockwise ){
        for (int i=0; i<4; i++) {
            front_face[i] = temp_front[(i+1)%4];
        }
        
        right_face[0]= temp_bottom[0];
        right_face[1]= temp_bottom[3];
        
        left_face[2] = temp_top[3];
        left_face[3] =temp_top[0];
        
        top_face[0] = temp_right[1];
        top_face[3] = temp_right[0];
        
        bottom_face[0] = temp_left[2];
        bottom_face[3] = temp_left[3];
    }
    
    if(frontFaceCounterClockwise){
        
        for (int i=0; i<4; i++) {
            front_face[i] = temp_front[(i+3)%4];
        }
        
        left_face[2] = temp_bottom[0];
        left_face[3] =temp_bottom[3];
        
        right_face[0]= temp_top[3];
        right_face[1]= temp_top[0];
        
        top_face[0] = temp_left[3];
        top_face[3] = temp_left[2];
        
        bottom_face[0] = temp_right[0];
        bottom_face[3] = temp_right[1];
    }
    
}

//rotating the cube altogether
//for viewing
//four types of moves
//turning right/left/up/down
//update each face accordingly

void
rotateAllCube(){
    int temp_right[4]; int temp_left[4]; int temp_top[4]; int temp_bottom[4]; int temp_front[4]; int temp_back[4];
    
    for (int i = 0; i<4; i++) {
        temp_right[i] = right_face[i];
        temp_bottom[i] = bottom_face[i];
        temp_left[i] = left_face[i];
        temp_top[i] = top_face[i];
        temp_front[i] = front_face[i];
        temp_back[i] = back_face[i];
    }
    
    if(turn_right){
        for (int i=0; i<4; i++) {
            front_face[i]=temp_right[i];
            right_face[i] = temp_back[i];
            left_face[i] = temp_front[i];
            back_face[i] = temp_left[i];
            bottom_face[i] = temp_bottom[(i+3)%4];
            top_face[i] = temp_top[(i+3)%4];
        }
    }
    if(turn_left){
        for (int i=0; i<4; i++) {
            front_face[i] = temp_left[i];
            right_face[i]= temp_front[i];
            left_face[i] = temp_back[i];
            back_face[i] = temp_right[i];
            bottom_face[i] = temp_bottom[(i+1)%4];
            top_face[i] = temp_top[(i+1)%4];
        }
    }
    
    if(turn_up){
        for (int i=0; i<4; i++) {
            right_face[i] = temp_back[(i+2)%4];
            left_face[i] = temp_front[(i+2)%4];
            front_face[i] = temp_left[(i+2)%4];
            back_face[i] = temp_right[(i+2)%4];
            
        }
        
        bottom_face[0] = temp_top[0]; bottom_face[1] = temp_top[3];
        bottom_face[2] = temp_top[2]; bottom_face[3] = temp_top[1];
        
        top_face[0] = temp_bottom[0]; top_face[1] = temp_bottom[3];
        top_face[2] = temp_bottom[2]; top_face[3] = temp_bottom[1];
    }
    
    if(turn_down){
        for (int i=0; i<4; i++) {
            right_face[i] = temp_back[(i+2)%4];
            left_face[i] = temp_front[(i+2)%4];
            front_face[i] = temp_left[(i+2)%4];
            back_face[i] = temp_right[(i+2)%4];
        }
        bottom_face[0] = temp_top[0]; bottom_face[1] = temp_top[3];
        bottom_face[2] = temp_top[2]; bottom_face[3] = temp_top[1];
        
        top_face[0] = temp_bottom[0]; top_face[1] = temp_bottom[3];
        top_face[2] = temp_bottom[2]; top_face[3] = temp_bottom[1];
    }
    
}

//keyboard functions
//turning up/down/right/left
//randomization performed
//help menu
//quit option

void
keyboard( unsigned char key,int x, int y )
{
    if(key == 'w' | key == 'W') turn_up=true;
    if(key == 's' | key == 'S') turn_down=true;
    if(key == 'a' | key == 'A') turn_left=true;
    if(key == 'd' | key == 'D') turn_right=true;
    if(key == 'r' | key == 'R')randomize=true;
    if(key == 'Q' | key == 'q') exit(0);
    if(key == 'h' | key == 'H'){
        std::cout<< "<3 The Amazing Rubic Cube <3"<<std::endl;
        std::cout<< " -Press Q to exit" << std::endl;
        std::cout<< " -Press D to rotate the whole cube right" << std::endl;
        std::cout<< " -Press A to rotate the whole cube left" <<std::endl;
        std::cout<< " -Press W to rotate the whole cube up" <<std::endl;
        std::cout<< " -Press S to rotate the whole cube down" <<std::endl;
         std::cout<< " -Click left/right to rotate faces clockwise/counter clockwise" <<std::endl;
    }
}

//----------------------------------------------------------------------------
//similar to pick function in-class exercise
//picks accordingly to color
//decides on which rotation to make
//6 possibilities
// for clockwise use right click
// for counterclockwise use left click

void mouse( int button, int state, int x, int y ){
    if ( state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray( vao[8] );
        model_view[8] =(RotateX( 45.0 ) * RotateY( -45.0 ) * RotateZ(0.0));
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view[8] );
        glDrawArrays( GL_TRIANGLES, 0, 288 );
        glFlush();
        
        y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
        unsigned char pixel[4];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        
        if (pixel[0]==0 && pixel[1]==0 && pixel[2]==255) topFaceClockwise=true;
        if(pixel[0]==255 && pixel[1]==0 && pixel[2]==0) frontFaceClockwise=true;
        if(pixel[0]==255 && pixel[1]==255 && pixel[2]==255) rightFaceClockwise=true;
        
        glutPostRedisplay();
        
    }
    
    else if ( state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray( vao[8] );
        model_view[8] =(RotateX( 45.0 ) * RotateY( -45.0 ) * RotateZ(0.0));
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view[8] );
        glDrawArrays( GL_TRIANGLES, 0, 288 );
        glFlush();
        
        unsigned char pixel[4];
        y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        
        if (pixel[0]==0 && pixel[1]==0 && pixel[2]==255) topFaceCounterClockwise=true;
        if(pixel[0]==255 && pixel[1]==0 && pixel[2]==0) frontFaceCounterClockwise=true;
        if(pixel[0]==255 && pixel[1]==255 && pixel[2]==255) rightFaceCounterClockwise=true;
        
        glutPostRedisplay();
    }
}

//3 types of movement
//the cube faces rotation
//cube rotating altogether left/right
//cube rotating altogether up/down

int moveOne = 1; int moveThree = 0; int moveTwo = 0;

//int solver_array[6];
//int solver_index=0;
//int solver_index2=5;

void timer( int p )
{
//    90 degree movement
    if(moveOne==90){
        rotateOneFace();
        rotateAllCube();
        moveOne=1;
        frontFaceCounterClockwise=frontFaceClockwise=false;
        topFaceCounterClockwise=topFaceClockwise=false;
        rightFaceCounterClockwise=rightFaceClockwise=false;
    }
    
//    90 degree movement
    if(moveTwo==90){
        rotateOneFace();
        rotateAllCube();
        moveTwo=0;
        turn_right=turn_left=false;
      
    }
    
//    180 degree movement
    if(moveThree==180){
        rotateOneFace();
        rotateAllCube();
        moveThree=0;
        turn_down=turn_up=false;
    }

    if(frontFaceClockwise) moveOne++;
    if(frontFaceCounterClockwise) moveOne++;
    if(topFaceClockwise)  moveOne++;
    if(topFaceCounterClockwise)  moveOne++;
    if( rightFaceClockwise )  moveOne++;
    if(rightFaceCounterClockwise)  moveOne++;
    if(turn_right) moveTwo++;
    if(turn_left) moveTwo++;
    if(turn_up)moveThree++;
    if(turn_down)moveThree++;
    
//    6 random movements performed
    if(random_counter==6){
        random_counter=0;
        randomize=false;
    }
   
//    if(solver_index2==0){
//        solver_index2=5;
//        solver=false;
//    }
//
    
    if(randomize && moveOne==1){
            int rando = (rand() % 6);
//           solver_array[solver_index]=rando;
            random_counter++;
//           solver_index++;
            if(rando==0) topFaceClockwise=true;
            if(rando==1) topFaceCounterClockwise=true;
            if(rando==2) rightFaceClockwise=true;
            if(rando==3) rightFaceCounterClockwise=true;
            if(rando==4) frontFaceClockwise=true;
            if(rando==5) frontFaceCounterClockwise=true;
        }
    
//     if(solver){
//
//              if(solver_array[solver_index2]==0) topFaceCounterClockwise=true;
//             if(solver_array[solver_index2]==1) topFaceClockwise=true;
//
//             if(solver_array[solver_index2]==2) rightFaceCounterClockwise=true;
//             if(solver_array[solver_index2]==3) rightFaceClockwise=true;
//
//             if(solver_array[solver_index2]==4) frontFaceCounterClockwise=true;
//             if(solver_array[solver_index2]==5) frontFaceClockwise=true;
//            solver_index2--;
// }

    glutPostRedisplay();
    glutTimerFunc(2,timer,0);
}

//----------------------------------------------------------------------------
int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize( 512, 512 );
    glutInitWindowPosition( 50, 50 );
    glutCreateWindow( "Amazing Rubic Cube" );
    glewExperimental = GL_TRUE;
    glewInit();
    init();
    glutDisplayFunc( display ); // set display callback function
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );
    glutKeyboardFunc(keyboard);
    glutTimerFunc(20,timer,0);
    glutMainLoop();
    return 0;
}
