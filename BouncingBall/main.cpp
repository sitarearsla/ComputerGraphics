//assignment1 - sitare arslanturk 57677
#define GL_SILENCE_DEPRECATION

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

//Update the xPosition and yPosition according to velocities.
//initial positions and variables

float initvalue = 2;
float x_pos=-initvalue;
float y_pos=initvalue;
float gravity = 0.0009;
const float friction = 0.009;
float v_x=0.003;
float v_y=0;

//pink
int ColorChoose = 3;
// start with sphere, vao
int oType = 1;

//Cube
//(6 faces)(2 triangles/face)(3 vertices/triangle)

const int NumVertices = 36;
point4 points[NumVertices];
color4 colors[NumVertices];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.33, -0.33,  0.33, 1.0 ),
    point4( -0.33,  0.33,  0.33, 1.0 ),
    point4(  0.33,  0.33,  0.33, 1.0 ),
    point4(  0.33, -0.33,  0.33, 1.0 ),
    point4( -0.33, -0.33, -0.33, 1.0 ),
    point4( -0.33,  0.33, -0.33, 1.0 ),
    point4(  0.33,  0.33, -0.33, 1.0 ),
    point4(  0.33, -0.33, -0.33, 1.0 )
};
// RGBA colors
color4 vertex_colors[8] = {
    
    
    color4( 1.0, 0.0, 0.0, 1.0 ),  //Red
    color4( 0.0, 1.0, 0.0, 1.0 ),  //Green
    color4( 0.0, 0.0, 1.0, 1.0 ),  //Blue
    color4( 1.0, 0.0, 1.0, 1.0 ),  //Magenta
    color4( 1.0, 1.0, 0.0, 1.0 ),  //Yellow
    color4( 0.0, 1.0, 1.0, 1.0 ),  //Cyan
    color4( 1.0, 1.0, 1.0, 1.0 ),  //White
    color4( 0.0, 0.0, 0.0, 1.0 )   //Black
};

// quad generates two triangles for each face
int Index = 0;
void
quad( int a, int b, int c, int d )
{
    points[Index] = vertices[a]; Index++; points[Index] = vertices[b]; Index++;
    points[Index] = vertices[c]; Index++; points[Index] = vertices[a]; Index++;
    points[Index] = vertices[c]; Index++; points[Index] = vertices[d]; Index++;
}
// generate 12 triangles: 36 vertices
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}
//-------------------------------------------------------------------------------
//Sphere

const int NumTimesToSubdivide = 5;
const int NumTriangles = 4096;

const int NumVerticesSphere = 3 * NumTriangles;

point4 pointSphere[NumVerticesSphere];
vec3 normals[NumVerticesSphere];

int IndexSphere = 0;
void
triangle( const point4& a, const point4& b, const point4& c )
{
    vec3 normal = normalize( cross(b - a, c - b) );
    normals[IndexSphere] = normal; pointSphere[IndexSphere] = a; IndexSphere++;
    normals[IndexSphere] = normal; pointSphere[IndexSphere] = b; IndexSphere++;
    normals[IndexSphere] = normal; pointSphere[IndexSphere] = c; IndexSphere++;
}
point4
unit( const point4& p )
{
    float len = p.x*p.x + p.y*p.y + p.z*p.z;
    point4 t;
    if ( len > DivideByZeroTolerance ) {
        t = p / sqrt(len);
        t.w = 1.0;
    }
    return t;
}
void
divide_triangle( const point4& a, const point4& b,
                const point4& c, int count )
{
    if ( count > 0 ) {
        point4 v1 = unit( a + b );
        point4 v2 = unit( a + c );
        point4 v3 = unit( b + c );
        divide_triangle( a, v1, v2, count - 1 );
        divide_triangle( c, v2, v3, count - 1 );
        divide_triangle( b, v3, v1, count - 1 );
        divide_triangle( v1, v3, v2, count - 1 );
    }
    else {
        triangle( a, b, c );
    }
}

void
tetrahedron( int count )
{
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, 1.0 ),
        vec4( 0.0, 0.942809, -0.333333, 1.0 ),
        vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
        vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };
    divide_triangle( v[0], v[1], v[2], count );
    divide_triangle( v[3], v[2], v[1], count );
    divide_triangle( v[0], v[3], v[1], count );
    divide_triangle( v[0], v[2], v[3], count );
}

//-----------------------------------------------------------------------------------------------------


enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int  Axis = Xaxis;

GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

GLuint  ModelView, Projection, ColorShift;
GLuint vao[2];

//multiple vao
void
init()
{
    //shaders
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    
    //-----Cube---------------------
    colorcube();
    // Create a vertex array object
    glGenVertexArrays( 2, vao );
    glBindVertexArray( vao[0] );
    // Create and initialize a buffer object
    GLuint buffer1;
    glGenBuffers( 1, &buffer1 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer1 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    
    //-Sphere------------------------
    tetrahedron( NumTimesToSubdivide );
    glBindVertexArray( vao[1] );
    // Create and initialize a buffer object with different name
    GLuint buffer2;
    glGenBuffers( 1, &buffer2 );
    glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(pointSphere) + sizeof(normals),NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(pointSphere), pointSphere );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(pointSphere), sizeof(normals), normals );
    // set up vertex arrays
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    ColorShift =glGetUniformLocation( program, "ColorShift" );
    
    glUseProgram( program );
    //Hidden surface removal
    glEnable( GL_DEPTH_TEST );
    // Clear Buffer
    glClearColor(1.0, 1.0, 1.0, 1.0 ); // white background
}

int numVerticestoBeDrawn[2]={NumVertices,NumVerticesSphere};

//Updates the position, view, and  color of the object
void
display( void )
{
    glBindVertexArray( vao[oType] );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mat4 model_view;
    
    vec3 displacement( x_pos, y_pos, 0.0 );
    
    model_view = (Scale(0.3, 0.3, 0.3) * Translate(displacement) * RotateX( Theta[Xaxis] ));
    
    //sets the color
    glUniform4fv(ColorShift,1,vertex_colors[ColorChoose]);
    
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    //    draws vertices
    glDrawArrays( GL_TRIANGLES, 0, numVerticestoBeDrawn[oType] );
    glutSwapBuffers();
}

//--------------------------------------------------------------------------------------------------------

void
reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    // The projection matrix
    mat4  projection;
    if (w <= h)
        projection = Ortho(-1.0, 1.0, -1.0 * ((GLfloat)h/(GLfloat)w), 1.0 * ((GLfloat)h/(GLfloat)w), -1.0, 1.0);
    else
        projection = Ortho(-1.0* ((GLfloat)w/(GLfloat)h), 1.0 *((GLfloat)w/(GLfloat)h), -1.0, 1.0, -1.0, 1.0);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    glDrawArrays( GL_TRIANGLES, 0, numVerticestoBeDrawn[oType] );
    glutSwapBuffers();
}
//--------------------------------------------------------------------------------------------------------

//keyboard functionalities

void
keyboard( unsigned char key, int x, int y )
{
    if(key == 'Q' | key == 'q')
        //        exit
        exit(0);
    
    if(key == 'I' | key == 'i'){
        //reset to initial state
        x_pos=-initvalue;
        v_x=0.003;
        y_pos=initvalue;
        v_y=0;
        gravity=0.0009;
    }
    if(key == 'h' | key == 'H'){
        //        help menu
        std::cout<< " The Amazing Bouncing Cube/Sphere"<<std::endl;
        std::cout<< " Choose the object type, fill style and color"<<std::endl;
        std::cout<< " -Press Q to exit" << std::endl;
        std::cout<< " -Press I to reset" << std::endl;
        std::cout<< " -Press H to get help" <<std::endl;
        std::cout<< " -Press left mouse button to reach menu" <<std::endl;
    }
}
//--------------------------------------------------------------------------------------------------------//
//Controls the animation inputs. At the end of each timer, updates the positions.
//Velocity in the x axis remains constant., in the y axis decreases.

void
timer( int t )
{
    x_pos += v_x;
    
    if(y_pos<-(2*initvalue)) {
        v_y *= -1;
        v_y-=friction;
        if(v_y<0){
            gravity=0;
            v_y=0;
            v_x=0;
        }
    }
    v_y -= gravity;
    y_pos += v_y;
    
    
    //    trying to rotate
    Theta[Axis] += 2.0;
    if ( Theta[Axis] > 360.0 ) {
        Theta[Axis] -= 360.0;
    }
    
    glutPostRedisplay();
    glutTimerFunc(10,timer,0);
}

//Menu
void
color_menu(int n){
    ColorChoose = n;
}

void
p_menu (int n){
    oType=n;
}

void
mode_menu (int n){
    if(n==0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else if(n==1){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void
mainMenu(int n){}



//--------------------------------------------------------------------------------------------------------//
int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize( 512, 1024 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "COMP410 IS AMAZING" );
    glewExperimental = GL_TRUE;
    glewInit();
    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc(keyboard);
    glutTimerFunc(5,timer,0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    int oMenu = glutCreateMenu(p_menu);
    glutAddMenuEntry("Cube", 0);
    glutAddMenuEntry("Sphere", 1);
    
    
    int dMenu = glutCreateMenu(mode_menu);
    glutAddMenuEntry("Line Mode", 0);
    
    glutAddMenuEntry("Solid Mode", 1);
    
    int cMenu = glutCreateMenu(color_menu);
    
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Magenta", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Cyan", 5);
    glutAddMenuEntry("White", 6);
    glutAddMenuEntry("Black", 7);
    
    glutCreateMenu(mainMenu);
    glutAddSubMenu("Object Type", oMenu);
    glutAddSubMenu("Drawing Mode", dMenu);
    glutAddSubMenu("Color Type", cMenu);
    
    glutAttachMenu(GLUT_LEFT_BUTTON);
    
    glutMainLoop();
    return 0;
}

