#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <math.h>
#include <vector>

float alpha = 0.5f;
float betta = 0.5f;
int u_number_steps = 100;

float angle = 0.0f;
float radius = 5.0f;

///     VECTOR FUNCTION

template <class T>
void print(std::vector<T> v) {
    std::cout << "(";
    for (int i = 0; i < v.size() - 1; i++){
        std::cout<< v[i] << ',';
    }
    std::cout << v[v.size() - 1] << ")\n";
}

template <typename T>
T ScalarMult(std::vector<T> v1, std::vector<T> v2){
    T sum = 0;
    for (int index = 0; index < std::min(v1.size(), v2.size()); index++){
        sum += v1[index] * v2[index];
    }
    return sum;
}

template <typename T>
float GetDistance(std::vector<T> v1, std::vector<T> v2){
    return std::sqrt((v1[0] - v2[0]) * (v1[0] - v2[0]) + (v1[1] - v2[1]) * (v1[1] - v2[1]) + (v1[2] - v2[2]) * (v1[2] - v2[2]));
}

template <typename T>
float GetLength(std::vector<T> v1){
    return sqrt(ScalarMult(v1, v1));
}

template <typename T>
float GetAngle(std::vector<T> v1, std::vector<T> v2){
    return std::acos(ScalarMult(v1, v2) / (GetLength(v1) * GetLength(v2)));
}

template <typename T>
std::vector<float> GetCentre(std::vector<std::vector<T>> v){
    std::vector<float> centre;
    centre.push_back((v[0][0] + v[1][0] + v[2][0]) / 3.0f);
    centre.push_back((v[0][1] + v[1][1] + v[2][1]) / 3.0f);
    centre.push_back((v[0][2] + v[1][2] + v[2][2]) / 3.0f);
    return centre;
}

template <typename T>
std::vector<float> Normalize(std::vector<T> v) {
    float len = GetLength(v);
    return {v[0] / len, v[1] / len, v[2] / len};
}

template <typename T>
std::vector<T> GetNormal(std::vector<T> v1, std::vector<T> v2, std::vector<T> v3){
    std::vector<T> line1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    std::vector<T> line2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};
    std::vector<T> res = {line1[1] * line2[2] - line2[1] * line1[2],
        line2[0] * line1[2] - line1[0] * line2[2], line1[0] * line2[1] - line2[0] * line1[1]};
    return Normalize(res);
}

std::vector<std::vector<std::vector<float>>> getCoordinates(){
    std::vector<std::vector<std::vector<float>>> v;
    int z_number_steps = 5;
    float u_step = (4 * M_PI) / u_number_steps;
    float z_step = 5 / z_number_steps;
    for (int z_index = 0; z_index < z_number_steps; z_index++){
        std::vector<std::vector<float>> vv;
        for (int u_index = 0; u_index < u_number_steps; u_index++){
            std::vector<float> node = {alpha * (u_index * u_step) * cosf(u_index * u_step), betta * (u_index * u_step) * sinf(u_index * u_step), -2 + z_index * z_step};
            vv.push_back(node);
        }
        v.push_back(vv);
    }
    return v;
}

std::vector<float> Transform(std::vector<float> point, std::vector<float> direction){
    std::vector<float> tmp = {0.0f, 0.0f, 0.1f};
    std::vector<float> v1_all = {tmp[1] * direction[2] - direction[1] * tmp[2],
        direction[0] * tmp[2] - tmp[0] * direction[2], tmp[0] * direction[1] - direction[0] * tmp[1]};
    std::vector<float> v2_all = {v1_all[1] * direction[2] - direction[1] * v1_all[2],
        direction[0] * v1_all[2] - v1_all[0] * direction[2], v1_all[0] * direction[1] - direction[0] * v1_all[1]};
    std::vector<float> v1 = Normalize(v1_all);
    std::vector<float> v2 = Normalize(v2_all);
    return {ScalarMult(point, v1), ScalarMult(point, v2)};
}

///         DRAW FUNCTION

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    
    float CameraX = cosf(angle) * 5.0f - sinf(angle) * 5.0f;
    float CameraY = sinf(angle) * 5.0f + cosf(angle) * 5.0f;
    std::vector<float> CameraCoordinates = {CameraX, CameraY, 5.0f};
    std::vector<float> direction = {CameraX, CameraY, 5.0f};
    
    float length_vector = GetLength(CameraCoordinates);
    float angle = M_PI / 2;
    float length_camera = 10;
    float height = (length_camera / 2) / tan(angle / 2);
    std::vector<float> PointCoordinates = {
        CameraCoordinates[0] - (CameraCoordinates[0] * height) / length_vector,
        CameraCoordinates[1] - (CameraCoordinates[1] * height) / length_vector,
        CameraCoordinates[2] - (CameraCoordinates[2] * height) / length_vector
    };
    std::vector<float> FlatCoordinates = {direction[0],
        direction[1], direction[2], -ScalarMult(direction, PointCoordinates)};
    
    std::vector<std::vector<std::vector<float>>> x = getCoordinates();
    std::vector<std::vector<std::vector<float>>> triangles;
    for (int i = 0; i < x.size() - 1; i++){
        for (int j = 0; j < x[i].size() - 1; j++){
            triangles.push_back({x[i][j], x[i + 1][j], x[i + 1][j + 1]});
            triangles.push_back({x[i][j], x[i][j + 1], x[i + 1][j + 1]});
        }
    }
    
    std::sort(triangles.begin(), triangles.end(), [CameraCoordinates](std::vector<std::vector<float>> t1, std::vector<std::vector<float>> t2) {
        return GetDistance(GetCentre(t1), CameraCoordinates) < GetDistance(GetCentre(t2), CameraCoordinates);
    });
    
    std::vector<std::vector<std::vector<float>>> NEWtriangles;
    for (int i = 0; i < triangles.size(); i++){
        std::vector<std::vector<float>> node;
        for (int j = 0; j < triangles[i].size(); j++){
            std::vector<float> XCoordinates = triangles[i][j];
            std::vector<float> LineCoordinates = {-XCoordinates[0] + CameraCoordinates[0], -XCoordinates[1] + CameraCoordinates[1], -XCoordinates[2] + CameraCoordinates[2]};
            if (GetAngle(LineCoordinates, direction) < angle / 2){
                float t = (-FlatCoordinates[3] - ScalarMult(FlatCoordinates, direction)) / (ScalarMult(FlatCoordinates, LineCoordinates));
                std::vector<float> XCoordinatesNEW = {CameraCoordinates[0] + t * LineCoordinates[0], CameraCoordinates[1] + t * LineCoordinates[1], CameraCoordinates[2] + t * LineCoordinates[2]};
                node.push_back(XCoordinatesNEW);
            } else {
                node.push_back({0});
            }
        }
        NEWtriangles.push_back(node);
    }
    for (int i = 0; i < NEWtriangles.size(); i++) {
        if ((NEWtriangles[i][0].size() + NEWtriangles[i][1].size() + NEWtriangles[i][2].size()) == 9) {
            std::vector<float> normal = GetNormal(NEWtriangles[i][0], NEWtriangles[i][1], NEWtriangles[i][2]);
            if (ScalarMult(normal, Normalize(direction)) < 0){
                normal[0] = -normal[0];
                normal[1] = -normal[1];
                normal[2] = -normal[2];
            }
            std::vector<float> Line = {CameraCoordinates[0] - GetCentre(NEWtriangles[i])[0], CameraCoordinates[1] - GetCentre(NEWtriangles[i])[1], CameraCoordinates[2] - GetCentre(NEWtriangles[i])[2]};
            float cosAngle = ScalarMult(normal, Normalize(Line));
            std::vector<std::vector<float>> points;
            for (int j = 0; j < NEWtriangles[i].size(); j++){
                std::vector<float> node = Transform(NEWtriangles[i][j], direction);
                points.push_back(node);
            }
            
            glBegin(GL_TRIANGLES);
                glColor3f(20.0f/255.0f * cosAngle * cosAngle, 20.0f/255.0f * cosAngle * cosAngle, 184.0f/255.0f * cosAngle * cosAngle);
                glVertex2f(points[0][0], points[0][1]);
                glVertex2f(points[1][0], points[1][1]);
                glVertex2f(points[2][0], points[2][1]);
            glEnd();
            
            glLineWidth(0.5f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex2f(points[0][0], points[0][1]);
                glVertex2f(points[1][0], points[1][1]);
            
                glVertex2f(points[1][0], points[1][1]);
                glVertex2f(points[2][0], points[2][1]);
            
                glVertex2f(points[2][0], points[2][1]);
                glVertex2f(points[0][0], points[0][1]);
            glEnd();
        }
    }
    glutSwapBuffers();
}

void idle() {
    angle += 0.01f;
    if (angle > 2 * M_PI) angle -= 2 * M_PI;
    display();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': alpha += 0.1f; break;
        case 'A': alpha -= 0.1f; break;
        case 'b': betta += 0.1f; break;
        case 'B': betta -= 0.1f; break;
        case '+':
        case '=': u_number_steps += 10; break;
        case '-': u_number_steps -= 10; break;
        case 27: exit(0);
    }
    display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("SPIRAL drawing");
    glClearColor(1, 1, 1, 1);
    glScalef(0.2, 0.2, 0);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
