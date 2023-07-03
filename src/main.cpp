#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <chrono>
#include <thread>

//Constantes
const float RGB[3][3] = {
    {1.0f, 0.0f, 0.0f},   // Rojo
    {0.0f, 1.0f, 0.0f},   // Verde
    {0.0f, 0.0f, 1.0f}    // Azul
};
// Variables de textura
GLuint textureID;
int textureWidth, textureHeight, textureChannels;
int j = 1;
bool WindowFlag = true;
bool Textura = true;

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
void readKeyboard(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        WindowFlag = false;
    }
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        Textura = true;
        j = 0;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        Textura = false;
        j = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        Textura = false;
        j = 2;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        Textura = false;
        j=3;
    }
}
void Show_Quad(int i, int j)
{
    if (Textura) {
        // Activa el uso de textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        // Dibuja el cuadrado con coordenadas de textura
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(Square_X[i][0], Square_Y[i][0]);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(Square_X[i][1], Square_Y[i][1]);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(Square_X[i][2], Square_Y[i][2]);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(Square_X[i][3], Square_Y[i][3]);
        glEnd();
    } else {
        // Utilizar color
        glColor3f(Colores[i][0], Colores[i][1],Colores[i][2]);
        glBegin(GL_QUADS);
        glVertex2f(Square_X[i][0], Square_Y[i][0]);
        glVertex2f(Square_X[i][1], Square_Y[i][1]);
        glVertex2f(Square_X[i][2], Square_Y[i][2]);
        glVertex2f(Square_X[i][3], Square_Y[i][3]);
        glEnd();
    }
}


// Función para cargar la imagen como textura
void LoadTexture(const char* imagePath)
{
    // Cargar imagen de textura
    unsigned char* image = stbi_load(imagePath, &textureWidth, &textureHeight, &textureChannels, 0);
    if (!image)
    {
        std::cout << "Failed to load texture image: " << imagePath << std::endl;
        return;
    }

    // Generar y vincular una textura
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurar parámetros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Cargar los datos de imagen en la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Liberar la memoria de la imagen
    stbi_image_free(image);
}


int main()
{
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window_width = mode->width;
    window_height = mode->height;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Proyecto Grafica", glfwGetPrimaryMonitor(), NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    // Configurar viewport
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Cargar textura
    LoadTexture("img/monaks.jpg");
    //LoadTexture("img/red.jpg", 1);
    //LoadTexture("img/green.jpg", 2);
    //LoadTexture("img/blue.jpg", 3);
    while (WindowFlag) {
        // ...
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        // Actualizar la posicion de los poligonos
        glfwSetCursorPosCallback(window, cursor_position_callback);
        
        //READ KEYBOARD
        readKeyboard(window);
        // Dibujar las caras del cubo
        for (int i = 0; i < 3; i++) {
            Show_Quad(i, j);    
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}