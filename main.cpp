#include<iostream>
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

using namespace std;

float camera_angle = 0;
float camera_x = 0;
float camera_y = 0;
float camera_height = 6;
float camera_rotate_speed = 0.003;
float camera_distance = 40;

float eye_x = 0;
float eye_y = 0;
float eye_z = 0;

float camera_x_angle = 0;
float camera_y_angle = 0;
float mouse_old_pos_x = 0;
float mouse_old_pos_y = 0;

GLboolean ambient = true;
GLboolean diffuse = true;
GLboolean specular = true;


GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 2.0, 25.0, 3.0, 1.0 };

GLfloat table_leg_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat table_leg_ambient[] = {0.627, 0.322, 0.176, 1.0};
GLfloat table_leg_diffuse[] = {0.627, 0.322, 0.176, 0.9};
GLfloat table_leg_specular[] = {0.627, 0.322, 0.176, 1.0};
GLfloat table_leg_shiness[] = {15};

GLfloat table_top_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat table_top_ambient[] = {0.824, 0.412, 0.118, 1.0};
GLfloat table_top_diffuse[] = {0.824, 0.412, 0.118, 0.9};
GLfloat table_top_specular[] = {0.824, 0.412, 0.118, 1.0};
GLfloat table_top_shiness[] = {17};

GLfloat chair_leg_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_leg_ambient[] = {1.000, 0.549, 0.000, 1.0};
GLfloat chair_leg_diffuse[] = {1.000, 0.549, 0.000, 0.9};
GLfloat chair_leg_specular[] = {1.000, 0.549, 0.000, 1.0};
GLfloat chair_leg_shiness[] = {15};

GLfloat chair_seat_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_seat_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_seat_diffuse[] = {1.000, 0.388, 0.278, 0.9};
GLfloat chair_seat_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat chair_seat_shiness[] = {17};

GLfloat chair_top_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat chair_top_ambient[] = {1.000, 0.627, 0.478, 1.0};
GLfloat chair_top_diffuse[] = {1.000, 0.627, 0.478, 0.9};
GLfloat chair_top_specular[] = {1.000, 0.627, 0.478, 1.0};
GLfloat chair_top_shiness[] = {17};

GLfloat bed_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat bed_ambient[] = {0.859, 0.439, 0.576, 1.0};
GLfloat bed_diffuse[] = {0.859, 0.439, 0.576, 0.9};
GLfloat bed_specular[] = {0.859, 0.439, 0.576, 1.0};
GLfloat bed_shiness[] = {13};

GLfloat bed_head_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat bed_head_ambient[] = {0.545, 0.271, 0.075, 1.0};
GLfloat bed_head_diffuse[] = {0.545, 0.271, 0.075, 0.9};
GLfloat bed_head_specular[] = {0.545, 0.271, 0.075, 1.0};
GLfloat bed_head_shiness[] = {13};

GLfloat shelf_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat shelf_ambient[] = {1.000, 0.388, 0.278, 1.0};
GLfloat shelf_diffuse[] = {1.000, 0.388, 0.278, 0.9};
GLfloat shelf_specular[] = {1.000, 0.388, 0.278, 1.0};
GLfloat shelf_shiness[] = {13};


GLfloat wall_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat wall_ambient[] = {0.373, 0.620, 0.627, 1.0};
GLfloat wall_diffuse[] = {0.373, 0.620, 0.627, 0.9};
GLfloat wall_specular[] = {0.373, 0.620, 0.627, 1.0};
GLfloat wall_shiness[] = {13};

GLfloat floor_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat floor_ambient[] = {0.184, 0.310, 0.310, 0.8};
GLfloat floor_diffuse[] = {0.184, 0.310, 0.310, 1.0};
GLfloat floor_specular[] = {0.184, 0.310, 0.310, 1.0};
GLfloat floor_shiness[] = {15};

GLfloat ceiling_no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat ceiling_ambient[] = {0.373, 0.620, 0.627, 1.0};
GLfloat ceiling_diffuse[] = {0.373, 0.620, 0.627, 0.9};
GLfloat ceiling_specular[] = {0.373, 0.620, 0.627, 1.0};
GLfloat ceiling_shiness[] = {15};

void lighting(GLfloat no_mat[4],GLfloat mat_ambient[4],GLfloat mat_diffuse[4],GLfloat mat_specular[4],GLfloat shiness[1])
{
    glEnable(GL_LIGHT0);
    if(ambient)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
        glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);

    }
    if(diffuse)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,no_mat);
    }
    if(specular)
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

    }
    else
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    }
    glMaterialfv(GL_FRONT,GL_SHININESS,shiness);
}

void draw_table()
{
    //table legs
    lighting(table_leg_no_mat,table_leg_ambient,table_leg_diffuse,table_leg_specular,table_leg_shiness);
    glPushMatrix();
    glScalef(.5,5,.5);
    glTranslatef(0,0,10);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glScalef(0.5,5,0.5);
    glTranslatef(0, 0, 22);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,5,0.5);
    glTranslatef(5, 0, 10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,5,0.5);
    glTranslatef(5, 0, 22);
    glutSolidCube(1);
    glPopMatrix();

    //table top
    lighting(table_top_no_mat,table_top_ambient,table_top_diffuse,table_top_specular,table_top_shiness);
    glPushMatrix();
    glTranslatef(0,3,8);
    glScalef(6,0.5,9);
    glutSolidCube(1);
    glPopMatrix();

}

void draw_shelf()
{
    lighting(shelf_no_mat,shelf_ambient,shelf_diffuse,shelf_specular,shelf_shiness);
    glPushMatrix();
    glTranslatef(15,0,-6);
    glRotatef(90,0,0,1);
    glScalef(12,2,6);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_chair(float x, float z, float r)
{
    //chair legs
    lighting(chair_leg_no_mat,chair_leg_ambient,chair_leg_diffuse,chair_leg_specular,chair_leg_shiness);
    glPushMatrix();
    glTranslatef(-4+x, -0.5, 9.5+z);
    glScalef(0.35,4,0.35);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4+x, -0.5, 6.5+z);
    glScalef(0.35,4,0.35);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7+x, -0.5, 9.5+z);
    glScalef(0.35,4,0.35);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7+x, -0.5, 6.5+z);
    glScalef(0.35,4,0.35);
    glutSolidCube(1);
    glPopMatrix();

    //chair seat
    lighting(chair_seat_no_mat,chair_seat_ambient,chair_seat_diffuse,chair_leg_specular,chair_seat_shiness);
    glPushMatrix();
    glTranslatef(-5.5+x, 1.5, 8+z);
    glScalef(4,1.0,4);
    glutSolidCube(1);
    glPopMatrix();

    //chair top
    if(r == 0)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-7.5+x, 3.5, 8+z);
        glRotatef(90,0,0,1);
        glScalef(4,0.3,3.8);
        glutSolidCube(1);
        glPopMatrix();
    }
    else if(r==1)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-8.0+x+2.5, 3.5, 8+z+1.8);
        glRotatef(90,1,0,0);
        glScalef(4,0.3,3.8);
        glutSolidCube(1);
        glPopMatrix();
    }
    else if(r==2)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-8.0+x+2.5, 3.5, 8+z-1.8);
        glRotatef(90,1,0,0);
        glScalef(4,0.3,3.8);
        glutSolidCube(1);
        glPopMatrix();
    }
    else if(r==3)
    {
        lighting(chair_top_no_mat,chair_top_ambient,chair_top_diffuse,chair_seat_specular,chair_top_shiness);
        glPushMatrix();
        glTranslatef(-7.5+x+4, 3.5, 8+z);
        glRotatef(90,0,0,1);
        glScalef(4,0.3,3.8);
        glutSolidCube(1);
        glPopMatrix();
    }
}

void draw_wall()
{
    lighting(wall_no_mat,wall_ambient,wall_diffuse,wall_specular,wall_shiness);
    glPushMatrix();
    glTranslatef(0,10,-25);
    glScalef(50,30,0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,10,0);
    glScalef(0.2,30,50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25,10,0);
    glScalef(0.2,30,50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,25);
    glScalef(50,30,0.2);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_floor()
{
    lighting(floor_no_mat,floor_ambient,floor_diffuse,floor_specular,floor_shiness);
    glPushMatrix();
    glTranslatef(0,-3,0);
    glScalef(50,0.2,50);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_ceiling()
{
    lighting(ceiling_no_mat,ceiling_ambient,ceiling_diffuse,ceiling_specular,ceiling_shiness);
    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(50,0.2,50);
    glutSolidCube(1);
    glPopMatrix();

}
void draw_bed()
{
    //bed
    lighting(bed_no_mat,bed_ambient,bed_diffuse,bed_specular,bed_shiness);
    glPushMatrix();
    glTranslatef(-4,0,-16);
    glScalef(12,3,6);
    glutSolidCube(1);
    glPopMatrix();

    //head
    lighting(bed_head_no_mat,bed_head_ambient,bed_head_diffuse,bed_head_specular,bed_head_shiness);
    glPushMatrix();
    glTranslatef(1.3,2.5,-16);
    glScalef(1.5,2.5,6);
    glutSolidCube(1);
    glPopMatrix();

}

void handleKeyPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        exit(0);
    case 'a':
    case 'A':
        camera_y = camera_y - 0.5;
        //center_z = center_z - 0.5;
        break;
    case 'd':
    case 'D':
        camera_y = camera_y + 0.5;
        //center_z = center_z + 0.5;
        break;
    case 'w':
    case 'W':
        camera_x = camera_x + 0.5;
        //center_x = center_x + 0.5;
        break;
    case 's':
    case 'S':
        camera_x = camera_x - 0.5;
        //center_x = center_x - 0.5;
        break;
    case 'u':
    case 'U':
        camera_x_angle+=.15;
        camera_y_angle+=.15;
        break;
    case 'k':
    case 'K':
        break;
    case 'h':
    case 'H':
        camera_x_angle-=.15;
        camera_y_angle-=.15;
        break;
    case 'j':
    case 'J':
        break;
    case '1':
        ambient=!ambient;
        break;
    case '2':
        diffuse=!diffuse;
        break;
    case '3':
        specular=!specular;
        break;
    }
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h)
{
    glViewport(0,0,w,h);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,5,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera_x, camera_height, camera_y, camera_x + cos(camera_x_angle), camera_height, camera_y + sin(camera_y_angle), 0, 1, 0);
    //gluLookAt(eye_x,eye_y,eye_z,center_x,center_y,center_z,0,1,0);
    draw_table();
    draw_chair(0.0,0,0);
    draw_chair(12.0,0,3);
    draw_chair(5.0,5.8,1);
    draw_chair(6.0,-5.8,2);

    draw_shelf();

    draw_wall();
    draw_floor();
    draw_ceiling();
    draw_bed();

    glTranslatef(4,2.5,-3);
    glScalef(0.7,0.5,0.7);
    //draw_memorial();
    glutSwapBuffers();

}

static void idle(void)
{
    glutPostRedisplay();
}



int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(100,100);

    glutCreateWindow("3d Room");
    initRendering();

    glClearColor(0,0,0,1);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPressed);
    glutReshapeFunc(handleResize);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
