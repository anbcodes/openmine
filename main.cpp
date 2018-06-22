#include <iostream>
#include <vector>
#include "linmath.h"
#include "glad.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std;

static const struct
{
  float x, y, z;
  float r, g, b;
} vertices[3] =
{
  { -0.6f, -0.4f, -0.1f, 1.f, 0.f, 0.f },
  {  0.6f, -0.4f, -0.1f, 0.f, 1.f, 0.f },
  {   0.f,  0.6f, -0.2f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
  "uniform mat4 MVP;\n"
  "attribute vec3 vCol;\n"
  "attribute vec3 vPos;\n"
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_Position = MVP * vec4(vPos, 1.0);\n"
  "    color = vCol;\n"
  "}\n";

static const char* fragment_shader_text =
  "varying vec3 color;\n"
  "void main()\n"
  "{\n"
  "    gl_FragColor = vec4(color, 1.0);\n"
  "}\n";

void GLCoords(int x, int y, vector<float>& shape, vector<float>& out) {

}

class Key {
  public:
    Key() {}
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
    }
};

class Mouse {
  public:
    static double x;
    static double y;

    Mouse(){}

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
      x = xpos;
      y = ypos;
    }

    static void button_callback(GLFWwindow* window, int button, int action, int mods) {
      if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
      }
    }
  //   static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  //
  //   }
};

double Mouse::x = 0.0;

double Mouse::y = 0.0;

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

int main()
{
  Key key;
  Mouse mouse;
  cout<<"Hello World!\n";
  if (!glfwInit()) {
    cout<<"DID NOT WORK";
  }
  glfwSetErrorCallback(error_callback);
  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window) {
    cout<<"ERROR";
  }
  int width, height;
  glfwSetKeyCallback(window, Key::key_callback);
  glfwSetMouseButtonCallback(window, Mouse::button_callback);
  glfwSetCursorPosCallback(window, Mouse::cursor_position_callback);
  glfwMakeContextCurrent(window);
  glfwGetFramebufferSize(window, &width, &height);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  // NOTE: OpenGL error checks have been omitted for brevity
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);
  glMatrixMode(GL_MODELVIEW);
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  GLint mvp_location = glGetUniformLocation(program, "MVP");
  GLint vpos_location = glGetAttribLocation(program, "vPos");
  GLint vcol_location = glGetAttribLocation(program, "vCol");
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 6, (void*) 0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 5, (void*) (sizeof(float) * 2));

  while (!glfwWindowShouldClose(window)) {
    float ratio;
    int width, height;
    mat4x4 m, p, mvp;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    // mat4x4_identity(m);
    // mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    // mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    // mat4x4_mul(mvp, p, m);
    // glUseProgram(program);
    // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 0.5f, 0.5f, -0.5f);
      glVertex3f(-0.5f, 0.5f, -0.5f);
      glVertex3f(-0.5f, 0.5f,  0.5f);
      glVertex3f( 0.5f, 0.5f,  0.5f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
