#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>
//Posiciones iniciales del cuadrado
float Square_X[3][4] = {
                        {-0.5f, 0.5f, 0.5f, -0.5f},
                        {-0.8f, -0.2f, -0.2f, -0.8f},
                        {-0.4f, 0.4f, 0.4f, -0.4f}
                        };

float Square_Y[3][4] = {
                        {0.5f, 0.5f, -0.5f, -0.5f},
                        {0.8f, 0.8f, 0.2f, 0.2f},
                        {0.4f, 0.4f, -0.4f, -0.4f}
                        };
//Dimensiones de la pantalla
int window_width = 800;
int window_height = 600;
//Imagen de prueba
int width, height, num_channels;
unsigned char* image_data = stbi_load("patricio.png", &width, &height, &num_channels, 0);


//Variables para saber que punto y de que cuadrado mover
int square_to_move = -1;
int point_to_move = -1;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Get cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

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
        Square_X[square_to_move][point_to_move] = window_x;
        Square_Y[square_to_move][point_to_move] = window_y;
    }
}

void Show_Quad(int i){
    glVertex2f(Square_X[i][0], Square_Y[i][0]);
    glVertex2f(Square_X[i][1], Square_Y[i][1]);
    glVertex2f(Square_X[i][2], Square_Y[i][2]);
    glVertex2f(Square_X[i][3], Square_Y[i][3]);
}

int main() {
    glfwInit();
 
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Mati is kinda Cringe ngl!!!!", NULL, NULL);
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
    while (!glfwWindowShouldClose(window)) {
        // Conseguir que punto de que poligono conseguir
        glfwSetMouseButtonCallback(window, mouse_button_callback);

        // Actualizar la posicion de los poligonos
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glClear(GL_COLOR_BUFFER_BIT);

        //Show Polygons on screen
        glBegin(GL_QUADS);
        Show_Quad(0);
        Show_Quad(1);
        Show_Quad(2);
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
 
    glfwTerminate();
    return 0;
}