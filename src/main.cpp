#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>

//Constantes
const float RGB[3][3] = {
    {1.0f, 0.0f, 0.0f},   // Rojo
    {0.0f, 1.0f, 0.0f},   // Verde
    {0.0f, 0.0f, 1.0f}    // Azul
};
#define SPEED 0.01
bool WindowFlag = true;

//Posiciones iniciales del cuadrado
float Square_X[3][4] = {
                        {-0.5f, 0.0f, 0.0f, -0.5},
                        {0.5f, 0.0f, 0.0f, 0.5f},
                        {-0.5f, 0.0f, 0.5f, 0.0f}
                        };

float Square_Y[3][4] = { 
                        { 0.5f, 0.34f, 0.0f, 0.15f},
                        {0.5f, 0.34f, 0.0f, 0.15f},
                        { 0.5f, 0.34f, 0.5f, 0.6f}
                        };
float Colores[3][3] = {
    {1.0f, 0.0f, 0.0f},   // Rojo
    {0.0f, 1.0f, 0.0f},   // Verde
    {0.0f, 0.0f, 1.0f}    // Azul
};

//Dimensiones de la pantalla
int window_width;
int window_height;

//Variables para saber que punto y de que cuadrado mover
int square_to_move = -1;
int point_to_move = -1;
//Mouse Functions
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Get cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int Inside = 1;
        // Convert cursor position from screen coordinates to window coordinates
        float window_x = ((float)xpos / (float)window_width) * 2.0f - 1.0f;
        float window_y = -(((float)ypos / (float)window_height) * 2.0f - 1.0f);

        // Check if cursor is inside triangle
        for(int j = 0; j < 3; j++){
            for (int i = 0; i < 4; i++) {
                float dx = Square_X[j][i] - window_x;
                float dy = Square_Y[j][i] - window_y;
                if (dx * dx + dy * dy < 0.001f) {
                    point_to_move = i;
                    square_to_move = j;
                    break;
                }
                if(dx * dx + dy * dy <= 0.01f && Inside != 0){
                    int temp = rand()%3;
                    Colores[j][0]= RGB[temp][0];
                    Colores[j][1]= RGB[temp][1];
                    Colores[j][2]= RGB[temp][2];
                    Inside = 0;
                    break;
                }
            }
        }

    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        // Release point
        point_to_move = -1;
        square_to_move = -1;
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (point_to_move >= 0) {
        // Convert cursor position from screen coordinates to window coordinates
        float window_x = ((float)xpos / (float)window_width) * 2.0f - 1.0f;
        float window_y = -(((float)ypos / (float)window_height) * 2.0f - 1.0f);

        // Update point position
        if (square_to_move == 0){
            switch(point_to_move){
                case 0:
                    Square_X[0][0] = window_x;
                    Square_Y[0][0] = window_y;

                    Square_X[2][0] = window_x;
                    Square_Y[2][0] = window_y;
                    break;
                case 1:
                    Square_X[0][1] = window_x;
                    Square_Y[0][1] = window_y;

                    Square_X[1][1] = window_x;
                    Square_Y[1][1] = window_y;

                    Square_X[2][1] = window_x;
                    Square_Y[2][1] = window_y;
                    break;
                case 2:
                    Square_X[0][2] = window_x;
                    Square_Y[0][2] = window_y;

                    Square_X[1][2] = window_x;
                    Square_Y[1][2] = window_y;
                    break;
                default:
                    Square_X[square_to_move][point_to_move] = window_x;
                    Square_Y[square_to_move][point_to_move] = window_y;
                    break;
            }
        }
        if (square_to_move == 1){
            switch(point_to_move){
                case 0:
                    Square_X[0][0] = window_x;
                    Square_Y[0][0] = window_y;

                    Square_X[2][2] = window_x;
                    Square_Y[2][2] = window_y;
                    break;
                case 1:
                    Square_X[0][1] = window_x;
                    Square_Y[0][1] = window_y;

                    Square_X[1][1] = window_x;
                    Square_Y[1][1] = window_y;

                    Square_X[2][1] = window_x;
                    Square_Y[2][1] = window_y;
                    break;
                case 2:
                    Square_X[1][2] = window_x;
                    Square_Y[1][2] = window_y;

                    Square_X[0][2] = window_x;
                    Square_Y[0][2] = window_y;
                    break;
                default:
                    Square_X[square_to_move][point_to_move] = window_x;
                    Square_Y[square_to_move][point_to_move] = window_y;
                    break;
            }
        }
        if (square_to_move == 2){
            switch(point_to_move){
                case 0:
                    Square_X[2][0] = window_x;
                    Square_Y[2][0] = window_y;

                    Square_X[0][0] = window_x;
                    Square_Y[0][0] = window_y;
                    break;
                case 1:
                    Square_X[0][1] = window_x;
                    Square_Y[0][1] = window_y;

                    Square_X[1][1] = window_x;
                    Square_Y[1][1] = window_y;

                    Square_X[2][1] = window_x;
                    Square_Y[2][1] = window_y;
                    break;
                case 2:
                    Square_X[2][2] = window_x;
                    Square_Y[2][2] = window_y;

                    Square_X[1][0] = window_x;
                    Square_Y[1][0] = window_y;
                    break;
                default:
                    Square_X[square_to_move][point_to_move] = window_x;
                    Square_Y[square_to_move][point_to_move] = window_y;
                    break;
            }
        }

    }
}

//Keyboard Functions
void readKeyboard(GLFWwindow* window, float *x, float *y){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        WindowFlag = false;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        *y += SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        *y -= SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        *x -= SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        *x += SPEED;
    }
}
void Show_Quad(int i){
    glColor3f(Colores[i][0], Colores[i][1], Colores[i][2]);

    glVertex2f(Square_X[i][0], Square_Y[i][0]);
    glVertex2f(Square_X[i][1], Square_Y[i][1]);
    glVertex2f(Square_X[i][2], Square_Y[i][2]);
    glVertex2f(Square_X[i][3], Square_Y[i][3]);
}

void ShowMobile(float* mobilex, float*mobiley){
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(mobilex[0], mobiley[0]);
    glVertex2f(mobilex[1], mobiley[1]);
    glVertex2f(mobilex[2], mobiley[2]);
    glVertex2f(mobilex[3], mobiley[3]);
}
void ModifyMobile(float* mobilex, float*mobiley, float x, float y){
    // 0->top left|1-> top right|2-> bottom right| 3-> bottom left
    if(mobilex[0]>= -1.0f || mobilex[3]>= -1.0f){
        mobilex[0]+=x;
        mobilex[1]+=x;
        mobilex[2]+=x;
        mobilex[3]+=x;
        mobiley[0]+=y;
        mobiley[1]+=y;
        mobiley[2]+=y;
        mobiley[3]+=y;
    }else{
        mobilex[0] = -0.99f;
        mobilex[3] = -0.99f;
    }
}

//Main Loop
int main() {
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window_width=mode->width;
    window_height=mode->height;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Mati is kinda Cringe ngl!!!!", glfwGetPrimaryMonitor(), NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //While principal
    //Activo mientras la ventana este activa
    float x_dir = 0.0f;
    float y_dir = 0.0f;
    // 0->top right|1-> top left|2-> bottom left| 3-> bottom right 
    float mobilex[4] = {-0.2f, 0.2f, 0.2f, -0.2f};
    float mobiley[4] = {0.2f, 0.2f, -0.2f, -0.2f};
    while (WindowFlag) {
        // READ MOUSE 
        // Conseguir que punto de que poligono conseguir
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        // Actualizar la posicion de los poligonos
        glfwSetCursorPosCallback(window, cursor_position_callback);
        
        //READ KEYBOARD
        readKeyboard(window, &x_dir, &y_dir);
        //MOVE SMOL SQUARE
        //ModifyMobile(mobilex, mobiley, x_dir, y_dir);
        glClear(GL_COLOR_BUFFER_BIT);
        //Show Polygons on screen
        glBegin(GL_QUADS);
        //ShowMobile(mobilex, mobiley);
        Show_Quad(0);
        Show_Quad(1);
        Show_Quad(2);
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        x_dir = 0.0f;
        y_dir = 0.0f;
    }
 
    glfwTerminate();
    return 0;
}