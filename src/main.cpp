#include <GL/glut.h>

#include <stdio.h>
#include <fstream>

#define TEX_HEIGHT 960 
#define TEX_WIDTH  679
#define TEX_CHANNEL 3

#define TEXTURE_FILENAME "src.txt"

static GLubyte img[TEX_HEIGHT][TEX_WIDTH][TEX_CHANNEL];
int tex_buf[TEX_HEIGHT * TEX_WIDTH * TEX_CHANNEL];

void readTextureData()
{
  FILE *fp;
  char buf[1024];
  fp = fopen(TEXTURE_FILENAME, "r");

  int counter = 0;
  while(fgets(buf, 1023, fp) != NULL) {
    if(counter == 0 || counter == 1 || counter == 2 || counter == 3) {
      counter++;
      continue;
    }

    tex_buf[counter - 4] = atoi(buf);

    counter++;
  }

  return;
}

void setTextureData()
{
  // 事前に読み込んだテクスチャデータを読み込む
  // ※ ここの処理で画像データからRGBを配列に入れている
  // 画像データがさし変わる場合にはこの処理を繰り返す
  for(int y=0; y<TEX_HEIGHT; y++) {
    for(int x=0; x<TEX_WIDTH; x++) {
      img[y][x][0] = tex_buf[y * TEX_WIDTH * TEX_CHANNEL + x * TEX_CHANNEL + 0];
      img[y][x][1] = tex_buf[y * TEX_WIDTH * TEX_CHANNEL + x * TEX_CHANNEL + 1];
      img[y][x][2] = tex_buf[y * TEX_WIDTH * TEX_CHANNEL + x * TEX_CHANNEL + 2];
    }
  }

  return;
}

void init()
{
  readTextureData();
  setTextureData();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_WIDTH, TEX_HEIGHT,   
            0, GL_RGB, GL_UNSIGNED_BYTE, img);

  return;
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 
          TEX_WIDTH, TEX_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, img);
  glBegin(GL_POLYGON);
    glTexCoord2d(0.0, 1.0); glVertex2f(-1.0, -1.0);
    glTexCoord2d(0.0, 0.0); glVertex2f(-1.0, 1.0);
    glTexCoord2d(1.0, 0.0); glVertex2f(1.0, 1.0);
    glTexCoord2d(1.0, 1.0); glVertex2f(1.0, -1.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();

  return;
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  return;
}

void idle()
{
  setTextureData();

  glutPostRedisplay();

  return;
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(TEX_WIDTH, TEX_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("recommended movie in 2023!!!");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}