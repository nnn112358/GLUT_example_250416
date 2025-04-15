#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// グローバル変数
int xBegin, yBegin;
int mButton;
float distance, twist, elevation, azimuth;
float xOrig = 0.0, yOrig = 0.0, zOrig = 0.0;

// 関数プロトタイプ
void polarview(void);
void resetview(void);
void display(void);
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void myKbd(unsigned char key, int x, int y);
void mySkey(int key, int x, int y);
void myInit(char *progname);

// 表示関数
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    // 視点の設定
    polarview();
    
    // 三角形の描画
    glColor3f(1.0, 0.0, 0.0);  // 赤色
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 1.0, 0.0);      // 上の頂点
        glVertex3f(-1.0, -1.0, 0.0);    // 左下の頂点
        glVertex3f(1.0, -1.0, 0.0);     // 右下の頂点
    glEnd();
    
    glPopMatrix();
    glutSwapBuffers();
}

// マウス入力判定
void myMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        switch(button) {
        case GLUT_LEFT_BUTTON:
            mButton = button;
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            mButton = button;
            break;
        }
        xBegin = x;
        yBegin = y;
    }
}

// マウス操作で座標変換
void myMotion(int x, int y)
{
    int xDisp, yDisp;
    
    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch (mButton) {
    case GLUT_LEFT_BUTTON:
        azimuth -= (float) xDisp/2.0;
        elevation -= (float) yDisp/2.0;
        break;
    case GLUT_RIGHT_BUTTON:
        distance += (float) xDisp/40.0;
        break;
    }
    xBegin = x;
    yBegin = y;
    glutPostRedisplay();
}

// キーボード入力
void myKbd(unsigned char key, int x, int y)
{
    switch(key) {
    case 'q':    // 終了
        exit(0);
        break;
    case 'c':    // 視点を中心に移動
        distance = 1.0;
        twist = 0.0;
        elevation = 0.0;
        azimuth = 0.0;
        break;
    case 'r':    // 視点をリセット
        resetview();
        break;
    }
    glutPostRedisplay();
}

// キーボードで移動（矢印キー）
void mySkey(int key, int x, int y)
{
    switch(key) {
    case GLUT_KEY_LEFT:
        xOrig += 0.2;
        break;
    case GLUT_KEY_RIGHT:
        xOrig -= 0.2;
        break;
    case GLUT_KEY_UP:
        yOrig += 0.2;
        break;
    case GLUT_KEY_DOWN:
        yOrig -= 0.2;
        break;
    case GLUT_KEY_PAGE_UP:
        zOrig -= 0.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        zOrig += 0.2;
        break;
    }
    glutPostRedisplay();
}

// 初期化
void myInit(char *progname)
{
    int width = 800, height = 600;
    float aspect = (float) width / (float) height;
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // コールバック関数の登録
    glutKeyboardFunc(myKbd);
    glutSpecialFunc(mySkey);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    
    // 深度バッファの有効化
    glEnable(GL_DEPTH_TEST);
    
    resetview();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// 視点のリセット
void resetview(void)
{
    distance = 5.0;
    twist = 0.0;
    elevation = 0.0;
    azimuth = 0.0;
}

// 視点の設定
void polarview(void)
{
    // マウスで移動
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0.0, 0.0, 1.0);
    glRotatef(-elevation, 1.0, 0.0, 0.0);
    glRotatef(-azimuth, 0.0, 1.0, 0.0);
    // キーボードで移動
    glTranslatef(xOrig, zOrig, yOrig);
}

// メイン関数
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit("GLUT Triangle with Rotation");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
