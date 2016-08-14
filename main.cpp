//
// Created by Hank O'Brien on 2/2/16.
//





#include <iostream>
#include <vector>
#include <OpenGL/gl3.h>
#include "GLFW/include/GLFW/glfw3.h"
#include "Graphics/Cell.h"
#include <thread>
#include <fstream>


using std::vector;

//const int appSize = 900;    //my screen height

const int cellResolution = 40;
const int cellCount = cellResolution * cellResolution;

enum RenderVar {DENSITY, VELOCITY, PRESSURE};

RenderVar renderStyle = DENSITY;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos); //sets pos values by modifying their references?
        std::cout << xpos << " " << ypos << "\n";
    }
}


void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_1 && action == GLFW_PRESS){
        //render with density here
        renderStyle = DENSITY;
    }
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS){
        //render with velocity here
        renderStyle = VELOCITY;
    }
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS){
        //render with pressure here
        renderStyle = PRESSURE;
    }
}

const vector<vector<Cell*>>& createFlatMatrix(float sideLength, int height, int width){
    vector<vector<Cell*>>* matrix = new vector<vector<Cell*>>;
    srand((unsigned int) time(NULL));
    for(int i = 0; i < height; i++){
        vector<Cell*>* row = new vector<Cell*>;
        for(int j = 0; j < width; j++){
            double fillerVal = (i * j) / ((double)width * height);
            Cell* cell = new Cell(sideLength, sideLength * j, sideLength * i, fillerVal, 1 / fillerVal, 0.5);
            row->push_back(cell);
        }
        matrix->push_back(*row);
    }
    return *matrix;
}

const std::vector<float>& getCoords(Cell* cell) {
    float x = cell->getX();
    float y = cell->getY();
    float size = cell->getSize();
    std::vector<float>* coords = new std::vector<float>;
    *coords = {
        x - 1, y - 1, 0.0f,
        x - 1 + size, y - 1, 0.0f,
        x - 1 + size, y - 1 + size, 0.0f,
        x - 1, y - 1 + size, 0.0f
    };
    return *coords;
}

//static unsigned int vertexBufferUniqueID = 0;


//std::vector<GLuint*> getMeshVertexArrayObjects(const Node &root){
//    std::vector<GLuint*> allVAOs;
//    std::vector<Node*> subNodes = root.getSubNodesAsList();
//    for(int i = 0; i < subNodes.size(); i++){
//        Node* node = subNodes[i];
//        GLuint tempBufferObject = vertexBufferUniqueID;
//        glGenBuffers(1, &tempBufferObject);
//        glBindBuffer(GL_ARRAY_BUFFER, tempBufferObject);
////        std::cout << node;
//        std::vector<float> points = getCoords(node);
////        std::cout << points[0] << " " << points[1] << " " << points[2] << " " << points[3];
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), &points[0], GL_STATIC_DRAW);
//
//        GLuint tempVertexArrayObject = 0;
//        glGenVertexArrays(1, &tempVertexArrayObject);
//        glBindVertexArray(tempVertexArrayObject);
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, tempBufferObject);
//        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//        allVAOs.push_back(&tempVertexArrayObject);
//        ++vertexBufferUniqueID;
//    }
//    return allVAOs;
//
//}

std::vector<double> getRgb(const Cell& cell, RenderVar renderVar){
    double h = 0;
    if(renderVar == DENSITY) {
        h = cell.getDensity() * 265.0 / 360;
    }else if(renderVar == VELOCITY){
        h = cell.getVelocity() * 265.0 / 360;
    }else if(renderVar == PRESSURE){
        h = cell.getPressure() * 265.0 / 360;
    }
    double s = 1;
    double l = 0.5;
    return colorConverter::hslToRgb(h, s, l);
}

const std::vector<GLuint>& getMeshVertexArrayObjects(const vector<vector<Cell *>>& matrix) {
    vector<GLuint>* allVAOs = new vector<GLuint>;
    for(int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < (matrix[i]).size(); j++)
        {
            Cell* cell_ptr = matrix[i][j];


            GLuint coordBuffer = 0;
            glGenBuffers(1, &coordBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
            std::vector<float> cellCoords = getCoords(cell_ptr);
            std::vector<float>* points = new std::vector<float>(cellCoords);   //todo: clean up memory
            cellCoords.clear();
            cellCoords.shrink_to_fit();
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*points).size(), &((*points)[0]), GL_STATIC_DRAW);
            points->clear();
            points->shrink_to_fit();


            GLuint colorBuffer = 1;
            glGenBuffers(1, &colorBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            std::vector<double> rgb = getRgb(*cell_ptr, renderStyle);
            double r = rgb[0];
            double g = rgb[1];
            double b = rgb[2];
//            std::cout << r << " " << g << " " << b << "\n";
            double colorVals[] = {
                    r, g, b,
                    r, g, b,
                    r, g, b,
                    r, g, b
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(colorVals), colorVals, GL_STATIC_DRAW);


            GLuint tempVertexArrayObject = 0;
            glGenVertexArrays(1, &tempVertexArrayObject);
            glBindVertexArray(tempVertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);

            allVAOs->push_back(tempVertexArrayObject);
        }
    }


    return *allVAOs;
}

Cell* updateCell(Cell* cell) {
    cell->update();
    return &(*cell);
}

const char* loadShaderFromFile(std::string path) {

    //opens file
    GLuint shaderID = 0;
    std::string* shaderString = new std::string();
    std::ifstream sourceFile(path.c_str());

    //load file
    if(sourceFile){
        shaderString->assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    }
    return shaderString->c_str();


}


void testCompiled(GLuint shader) {
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog((unsigned long) maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }
    }
}




int main(void) {

    GLFWwindow *window;

//    Initialize the library
    if (!glfwInit()) {
        return -1;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(mode->height, mode->height, "CFD", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    float leftPoints[] =
            {
                -0.1f,  0.1f,  0.0f,
                0.2f, 0.2f,  0.0f,
                0.3f, -0.3f, 0.0f,
                -0.4f, -0.4f, 0.0f
             };


    GLuint vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof(leftPoints), leftPoints, GL_STATIC_DRAW);

    float otherPoints[] =
            {
                   0.1f, 0.1f, 0.0f,
                   0.0f, 0.0f, 0.0f,
                   -0.1f, 0.1f, 0.0f
            };

    double otherColors[] =
            {
                    1, 1, 1,
                    1, 1, 1,
                    1, 1, 1
            };

    GLuint otherVbo = 1;
    glGenBuffers(1, &otherVbo);
    glBindBuffer(GL_ARRAY_BUFFER, otherVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(otherPoints), otherPoints, GL_STATIC_DRAW);

    GLuint otherColorBuffer = 1;
    glGenBuffers(1, &otherColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, otherColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(otherColors), otherColors, GL_STATIC_DRAW);


    vector<vector<Cell*>> matrix = createFlatMatrix((float) (2.0 / cellResolution), cellResolution, cellResolution);

    std::vector<GLuint> vertexArrayObjects = getMeshVertexArrayObjects(matrix);


    glfwSetKeyCallback(window, key_callback);


    const char* vertex_shader_string = loadShaderFromFile("/Users/Hank/ClionProjects/CFD/Graphics/VertexShader.txt");

    const char* fragment_shader_string = loadShaderFromFile("/Users/Hank/ClionProjects/CFD/Graphics/FragmentShader.txt");


    GLuint vertex_shader = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vertex_shader, 1, &vertex_shader_string, NULL);
    glCompileShader (vertex_shader);
    testCompiled(vertex_shader);

    GLuint fragment_shader = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fragment_shader, 1, &fragment_shader_string, NULL);
    glCompileShader (fragment_shader);
    testCompiled(fragment_shader);

    GLuint shader_program = glCreateProgram ();
    glAttachShader (shader_program, fragment_shader);
    glAttachShader (shader_program, vertex_shader);
    glLinkProgram (shader_program);

    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // GL_CW for clock-wise

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose (window))
    {
        // wipe the drawing surface clear
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (shader_program);


        //allows me to use many VertexArrayObjects but draw them in a clean way
        for(GLuint shape : vertexArrayObjects){
            // draw points 0-4 from the currently bound VAO with current in-use shader
            glBindVertexArray(shape);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //4 is the number of points it will draw
        }
        // update other events like input handling
        glfwPollEvents ();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers (window);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        if (glfwGetKey (window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose (window, 1);
        }


//        std::thread c = std::thread(updateCell, *(matrix[0][0]));
//        c.join();
        std::thread cellUpdateThreads[cellCount];
        short counter = 0;
        for(int i = 0; i < cellResolution; i++){
            for(int j = 0; j < cellResolution; j++) {
                cellUpdateThreads[counter] = std::thread(updateCell, (matrix[i][j]));
//                updateCell(*matrix[i][j]);
                counter++;
            }
        }

        for(int i = 0; i < cellCount; i++){
            cellUpdateThreads[i].join();
        }
        vertexArrayObjects.clear();
        vertexArrayObjects.shrink_to_fit();
        vertexArrayObjects = getMeshVertexArrayObjects(matrix);


    }

    glDeleteShader(vertex_shader);
    delete[] vertex_shader_string;
    glDeleteShader(fragment_shader);
    delete[] fragment_shader_string;

    glfwTerminate();
    vertexArrayObjects.clear();
    return 0;
}

//int main(){
//    double x = 0;
//    double y = 1;
//    double endX = 1;
//    int stepCount = (int)(pow(2,6));
//    std::clock_t clock = std::clock();
//    auto start = std::chrono::high_resolution_clock::now();
////        RK4
//    double stepLength = 0.0625/4;
//    printf("fixed step\n");
//    std::vector<double> a = integrate(x,y,stepCount, stepLength, [](double x, double y){
//        return y; //function to integrate
//    });
//
//////        RK45 Embedded
////        double maxErrorFrac = 0.00000000000000001;
////    printf("Embedded\n");
////    std::vector<double> a = embeddedIntegrate(x, endX, y, maxErrorFrac, [](double x, double y) {
////        return y;
////    });
//
//////        RK4 Step-doubling
////    double maxErrorFrac = 0.0000001;
////    printf("Step Doubling\n");
////    std::vector<double> a = doublingIntegrate(x, y, endX, maxErrorFrac, [](double x, double y) {
////        return y;
////    });
//
//    auto end = std::chrono::high_resolution_clock::now();
//    printf("%.10f\n", a.back());
//    printf("Error: %.15f", exp(1.0) - a.back());    //gets e - answer to find accuracy for f(x) = e^x
//    cout << "\n Runtime micros: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//
////    double **coefficients;
////    coefficients = new double*[2];
////    coefficients[0] = new double[2];
////    coefficients[1] = new double[2];
////    coefficients[0][0] = 4;
////    coefficients[0][1] = -2;
////    coefficients[1][0] = 3;
////    coefficients[1][1] = -1;
////
////    uncouple(coefficients, 0, 1, 2);



//}



