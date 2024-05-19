#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"AllMyInclude.h"

#define fov 30.0f
#define degres 0.0174f
#define ScreenHeight 768
#define ScreenLenght 1366
float spaceing = 2.0f/fov;
const float pi = 3.14f;

float offsety;
float startor;
float deltatime;
float movespeed= 0.1f;
float rotationspeed = 0.1f;

vec2 playerpos = { 12.0f,5.0f };
vec2 dir = { -1,0.0f };

int quality =3;

float time1, time2;
vec2 mousep;
POINT mousepos;
bool shoted;

int main(void)
{
    GLFWwindow* window;
    
   
    if (!glfwInit())
        return -1;

   
    window = glfwCreateWindow(ScreenLenght, ScreenHeight, "doom 3d", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR not glew!!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    

    shader Shader("Basic.shader");
    shader TextureShader("texture.shader");
    

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    
    float startspace = (float)(spaceing-1.00f);
    float pos[] = {
      -1.0f, 1.0f,//0
      -1.0f,-1.0f,//1
      startspace, 1.0f,//2
      startspace,-1.0f//3
    };

    unsigned int indices[] = {
        0,1,2,2,3,1
    };
    unsigned int VAO, VAB, IBO;

    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VAB);
    glBindBuffer(GL_ARRAY_BUFFER, VAB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6  * 2, pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,(void*)0);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    float postop[] = {
      -1.0f, 1.0f,//0
      -1.0f, 0.0f,//1
       1.0f, 1.0f,//2
       1.0f, 0.0f//3
    };
    float posbotm[] = {
      -1.0f, 0.0f,//0
      -1.0f,-1.0f,//1
       1.0f, 0.0f,//2
       1.0f,-1.0f//3
    };
    
    unsigned int  VAO1, VAO2, VAB1, VAB2, IBO1, IBO2, VAO3, VAB3, IBO3;

    glCreateVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glGenBuffers(1, &VAB1);
    glBindBuffer(GL_ARRAY_BUFFER, VAB1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, postop, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    
    glGenBuffers(1, &IBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glCreateVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &VAB2);
    glBindBuffer(GL_ARRAY_BUFFER, VAB2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, posbotm, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glGenBuffers(1, &IBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    float posarm[] = {
           0.5f,-0.1f,0,1,//0
           0.5f,-1.1f,0,0,//1
           1.0f,-0.1f,1,1,//2
           1.0f,-1.1f,1,0//3
    };

    glCreateVertexArrays(1, &VAO3);
    glBindVertexArray(VAO3);
    glGenBuffers(1, &VAB3);
    glBindBuffer(GL_ARRAY_BUFFER, VAB3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, posarm, GL_STATIC_DRAW);   
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &IBO3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
     
    Textur gun("gun1.png");
    Textur gunshot("gun2.png");
    map map1("mapianis.mamaie");
    map map2("map.map");
    map activemap=map2;
    int i;
    Renderer renderer(activemap);
    Raycaster raycaster(activemap);
    int lastoffsety;
    float woble;
    bool in;
    bool locked = 0;
    while (!glfwWindowShouldClose(window))
    {

        deltatime = time2 - time1;
        time1 = glfwGetTime();
        renderer.ClearScreen();
        renderer.ClearConsole();
        renderer.rendermap(playerpos);
        ImGui_ImplGlfwGL3_NewFrame();

        GetCursorPos(&mousepos);

        if (locked) {
            SetCursorPos(ScreenLenght / 2, ScreenHeight / 2);
            input(activemap, raycaster, rotationspeed, movespeed, playerpos, dir, deltatime, offsety,
                lastoffsety, woble, in, { (float)mousepos.x - ScreenLenght / 2,(float)mousepos.y - ScreenHeight / 2 }, shoted, locked);
        }
        else {
            input(activemap, raycaster, rotationspeed, movespeed, playerpos, dir, deltatime, offsety,
                lastoffsety, woble, in, { (float)mousepos.x - mousep.x,mousep.y - (float)mousepos.y }, shoted, locked);
            ShowCursor(true);
        }
        if(ShowCursor(false) >= 0 && locked){
           ShowCursor(false);
        }
        else {
           ShowCursor(true);
        }

        mousep = { (float)mousepos.x,(float)mousepos.y };
        gun.UnBind();
        Shader.Bind();
        Shader.SetUniform1f("offsety", 0);
        
        glBindVertexArray(VAO1);
        Shader.SetUniform1i("coltipe", 1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(VAO2);
        Shader.SetUniform1i("coltipe", 2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glBindVertexArray(VAO);
        Shader.Bind();
        Shader.SetUniform1f("offsety", offsety);
        renderer.render(Shader, raycaster, dir, playerpos, quality, fov,spaceing);


        Shader.SetUniform1f("depth", 1);
        Shader.SetUniform1f("offsetx", 0);
        Shader.Unbind();
        gun.Bind(0);
        if (shoted) {
            gunshot.Bind(0);
            shoted = false;
        }
        TextureShader.Bind();
        TextureShader.SetUniform1f("offsety", offsety * 4);
        TextureShader.SetUniform1i("u_Texture", GL_TEXTURE0);
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        std::stringstream ss;
        
        ss << "dir:" << dir.x << " " << dir.y;
        
        ss << "\nplayer:" << playerpos.x << " " << playerpos.y;
        ss << "\nray dis:" <<raycaster.ShotRayAccurate(playerpos,dir).dis;
        std::string cout = ss.str();
        
        ImGui::Text(cout.c_str());
        ImGui::SliderFloat("roation speed", &rotationspeed, 0.0f, 5.0f);
        ImGui::SliderFloat("move speed", &movespeed, 0.0f, 5.0f);
        ImGui::SliderInt("quality:", &quality, 0, 10);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

       
        glfwSwapBuffers(window);

        glfwPollEvents();
        time2 = glfwGetTime();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

