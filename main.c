#include <stdio.h>
#include <Windows.h>
#include <WindowsX.h>
#include <GL/glew.h>

#include "mglm.h"
#include "mglu.h"
#include "mat.h"
#include "vec.h"

#include "shader.h"
#include "player.h"

#include "object.h"
#include "light.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"

static const LONG INIT_WIDTH_CLIENT = 512;
static const LONG INIT_HEIGHT_CLIENT = 512;
static const BOOL ANIMATION = TRUE;
static const int FRAME_RATE = 60;

static Player player;
static KeysPressed keysPressed = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};

static GLuint shader;

static Object ground;
static Object wall;
static Object cube;

static GLint loc_vertex;
static GLint loc_normal;
static GLint loc_tangent;
static GLint loc_texCoord;
static AttribLocations attribLocations;

static GLuint texture0;
static GLuint texture1;
static GLuint texture2;
static GLuint texture3;

static float lightAmb[] = {0.1f, 0.1f, 0.1f, 1.0f};
static float lightDif[] = {0.9f, 0.9f, 0.9f, 1.0f};
static float lightSpc[] = {1.0f, 1.0f, 1.0f, 1.0f};
static float lightPos[] = {0.0f, 0.5f, 0.0f, 1.0f};
static struct Light light;

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static void create(HWND window, CREATESTRUCTW* createStruct);
static void resize(HWND window, WORD width_client, WORD height_client);
static void keyDown(HWND window, WPARAM key, LPARAM extra);
static void keyUp(HWND window, WPARAM key, LPARAM extra);
static void mouseMove(HWND window, WPARAM keys, int x, int y);
static void render();
static void update(HWND window, WPARAM wParam, LPARAM lParam);
static void destroy(HWND window);
static void grid(float radius);
void checkErrors(HWND window, int lineNumber);
static void mglErrorText(char* buffer, size_t count, GLenum errorCode);

// wWinMain takes cmd arguments as wchar_t
// instance_prev is irrelevant, was used in 16-bit Windows
// cmdLine contains cmd args
// cmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally

int WINAPI WinMain(HINSTANCE instance, HINSTANCE instance_prev, PSTR cmdLine, int cmdShow)
{
    int ret = 1;
    const char* windowClassName = "Sample window class";
    const char* windowName = "My window";
    WNDCLASS windowClass;
    RECT windowRect;
    HWND window = NULL;
    MSG message;
    BOOL messageStatus = 0;

    // setup window class
    memset(&windowClass, 0, sizeof(WNDCLASS));
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.lpszClassName = windowClassName;
    RegisterClass(&windowClass);

    // calc window size based on client size
    windowRect.left = 0;
    windowRect.right = INIT_WIDTH_CLIENT;
    windowRect.top = 0;
    windowRect.bottom = INIT_HEIGHT_CLIENT;
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // create window w/ extended parameters
    window = CreateWindowEx
    (
        0,
        windowClassName,
        windowName,
        WS_OVERLAPPEDWINDOW,    // standard window
        CW_USEDEFAULT,          // default pos
        CW_USEDEFAULT,          // default pos
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,                   // parent
        NULL,                   // menu
        instance,
        NULL                    // additional info via CREATESTRUCT structure
    );

    if (window)
    {
        // fullscreen
        ShowWindow(window, 3);

        // init message
        memset(&message, 0, sizeof(MSG));

        // 0 : WM_QUIT
        // -1 : error
        while ((messageStatus = GetMessage(&message, window, 0, 0)) > 0) // when hWnd, thread doesn't exit?!?
        {
            TranslateMessage(&message); // turn virtual-key messages into char messages
            DispatchMessage(&message); // send message to WindowProc
        }

        // WM_QUIT : success
        if (messageStatus == 0)
        {
            ret = 0;
        }
    }

    return ret;
}

// while WindowProc is running, blocks any other messages for windows created on the same thread
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret_val = 0;
    
    switch (message)
    {
    case WM_CREATE:

        create(window, (CREATESTRUCTW*)lParam);
        break;

    case WM_SIZE:

        // these are in CLIENT coordinates
        resize(window, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_PAINT:

        {
            PAINTSTRUCT paintStruct;
            // fills paintStruct w/ info on the repaint request
            HDC dc = BeginPaint(window, &paintStruct);

            // fills in update-region (rcPaint)
            //FillRect(dc, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW+1));

            render();
            SwapBuffers(dc);

            // clears update region
            EndPaint(window, &paintStruct);
        }

        break;

    case WM_TIMER:

        update(window, wParam, lParam);
        break;

    case WM_KEYDOWN:

        keyDown(window, wParam, lParam);
        break;

    case WM_KEYUP:

        keyUp(window, wParam, lParam);
        break;

    case WM_MOUSEMOVE:

        mouseMove(window, wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_CLOSE: // when X is click, ALT+F4 etc.

        // posts WM_DESTROY message
        DestroyWindow(window);
        break;

    case WM_DESTROY:
        
        // posts WM_QUIT message
        // closes thread with exit value: 0
        PostQuitMessage(0);
        break;

    default:

        // handle all other messages
        ret_val = DefWindowProcW(window, message, wParam, lParam);
    }

    return ret_val;
}

#include "vector.h"

void create(HWND window, CREATESTRUCTW* createStruct)
{
    Vertex ground_vertexBuffer[4];
    Vertex wall_vertexBuffer[8];
    unsigned int ground_indexBuffer[6];
    unsigned int wall_indexBuffer[12];
    
    unsigned int pixelFormat;
    HDC dc;
    HGLRC rc;
    PIXELFORMATDESCRIPTOR pfd;
    GLuint vert;
    GLuint frag;
    
    ShowCursor(FALSE);
    
    dc = GetDC(window);

    if (dc)
    {
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

        // Initialize pfd.
        pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion    = 1;
        // Layer and buffering information.
        pfd.dwFlags     = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.dwLayerMask = PFD_MAIN_PLANE;
        pfd.iLayerType  = PFD_MAIN_PLANE;
        // Pixel type.
        pfd.iPixelType  = PFD_TYPE_RGBA;
        // Specify minimum number of bitplanes for each buffer;
        pfd.cColorBits   = 24; // NOTE: this number must exclude alpha
        pfd.cDepthBits   = 32;
        pfd.cStencilBits = 0;
        pfd.cAccumBits   = 0;

        // Attempts to match a supported pixel format to the info requested in the PIXELFORMATDESCRIPTOR struct.
        pixelFormat = ChoosePixelFormat(dc, &pfd);
    
        if (pixelFormat)
        {
            // Sets pixel format to that which was generated.
            if (SetPixelFormat(dc, pixelFormat, &pfd))
            {
                rc = wglCreateContext(dc);
    
                if (rc)
                {
                    if (wglMakeCurrent(dc, rc))
                    {
                        if (glewInit() == GLEW_OK)
                        {
                            if (ANIMATION)
                            {
                                SetTimer(window, 0, 1000 / FRAME_RATE, NULL);
                            }
                            
                            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                            
                            glEnable(GL_DEPTH_TEST);
                            glEnable(GL_CULL_FACE);
                            glFrontFace(GL_CCW);
                            glShadeModel(GL_SMOOTH);
                            glPolygonMode(GL_FRONT, GL_FILL);
                            //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

                            /*
                            glEnable(GL_FOG);
                            glFogf(GL_FOG_MODE, GL_EXP2);
                            glFogf(GL_FOG_START, 0.0f);
                            glFogf(GL_FOG_END, 1.0f);
                            glFogf(GL_FOG_DENSITY, 0.02f);
                            */

                            /*
                            glEnable(GL_LIGHT0);
                            glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
                            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
                            glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
                            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
                            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
                            glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
                            glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0025f);
                            */

                            vec4_set(light.position, 0.0f, 1.0f, 0.0f, 1.0f);
                            vec4_set(light.ambient, 0.1f, 0.1f, 0.1f, 1.0f);
                            vec4_set(light.diffuse, 0.9f, 0.9f, 0.9f, 1.0f);
                            vec4_set(light.specular, 1.0f, 1.0f, 1.0f, 1.0f);
                            light.intensity = 2.0f;
                            light.attenuation = 0.0025f;
                            light.radius = 50.0f;

                            vert = createShader("normal.vert", GL_VERTEX_SHADER);
                            frag = createShader("normal.frag", GL_FRAGMENT_SHADER);
                            shader = createProgram(vert, frag);

                            glUniform1i(glGetUniformLocation(shader, "texture_diffuse"), 0);
                            glUniform1i(glGetUniformLocation(shader, "texture_normal"), 1);

                            genDefaultTextures();

                            ground.mesh = (Mesh*)malloc(sizeof(Mesh));
                            ground.material = (Material*)malloc(sizeof(Material));
                            wall.mesh = (Mesh*)malloc(sizeof(Mesh));
                            wall.material = (Material*)malloc(sizeof(Material));
                            cube.mesh = (Mesh*)malloc(sizeof(Mesh));
                            cube.material = (Material*)malloc(sizeof(Material));

                            vec4_set(ground.material->ambient, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(ground.material->diffuse, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(ground.material->specular, 0.05f, 0.05f, 0.05f, 1.0f);
                            vec4_set(ground.material->emission, 0.0f, 0.0f, 0.0f, 1.0f);
                            ground.material->shininess = 16.0f;
                            texture_create("textures\\stone.bmp", &ground.material->texture0);
                            texture_create("textures\\stone_NRM.bmp", &ground.material->texture1);
                            
                            vec4_set(wall.material->ambient, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(wall.material->diffuse, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(wall.material->specular, 0.1f, 0.1f, 0.1f, 1.0f);
                            vec4_set(wall.material->emission, 0.0f, 0.0f, 0.0f, 1.0f);
                            wall.material->shininess = 16.0f;
                            texture_create("textures\\brick.bmp", &wall.material->texture0);
                            texture_create("textures\\brick_NRM.bmp", &wall.material->texture1);
                            
                            vec4_set(cube.material->ambient, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(cube.material->diffuse, 0.5f, 0.5f, 0.5f, 1.0f);
                            vec4_set(cube.material->specular, 0.1f, 0.1f, 0.1f, 1.0f);
                            vec4_set(cube.material->emission, 0.0f, 0.0f, 0.0f, 1.0f);
                            cube.material->shininess = 16.0f;
                            texture_create("textures\\grass.bmp", &cube.material->texture0);
                            texture_create("textures\\grass_NRM.bmp", &cube.material->texture1);
                            //cube.material->texture1 = DEFAULT_NORMAL_TEXTURE;

                            memset(&player, 0, sizeof(Player));
                            player.width = 0.5f;
                            player.height = 2.0f;
                            player.speed = 0.075f;
                            player.sensitivity = 0.4f;
                            player.runFactor = 1.5f;
                            player.crouchFactor = 0.5f;
                            player.jumpSpeed = 8.96112f / 50.0f;
                            player.view.fov = 53.130102354155978703144387440907f;
                            player.view.aspect = (float)INIT_WIDTH_CLIENT / (float)INIT_HEIGHT_CLIENT;
                            player.view.zNear = 0.1f;
                            player.view.zFar = 100.0f;

                            loc_vertex = glGetAttribLocation(shader, "vertex");
                            loc_normal = glGetAttribLocation(shader, "normal");
                            loc_tangent = glGetAttribLocation(shader, "tangent");
                            loc_texCoord = glGetAttribLocation(shader, "texCoord");

                            attribLocations.position = loc_vertex;
                            attribLocations.normal = loc_normal;
                            attribLocations.tangent = loc_tangent;
                            attribLocations.texCoord = loc_texCoord;

                            vec3_set((float*)&ground_vertexBuffer[0].position, 2.5f, 0.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[1].position, 2.5f, 0.0f, -50.0f);
                            vec3_set((float*)&ground_vertexBuffer[2].position, -2.5f, 0.0f, -50.0f);
                            vec3_set((float*)&ground_vertexBuffer[3].position, -2.5f, 0.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[0].normal, 0.0f, 1.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[1].normal, 0.0f, 1.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[2].normal, 0.0f, 1.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[3].normal, 0.0f, 1.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[0].tangent, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[1].tangent, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[2].tangent, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&ground_vertexBuffer[3].tangent, 1.0f, 0.0f, 0.0f);
                            vec2_set((float*)&ground_vertexBuffer[0].texCoord, 5.0f, 0.0f);
                            vec2_set((float*)&ground_vertexBuffer[1].texCoord, 5.0f, 50.0f);
                            vec2_set((float*)&ground_vertexBuffer[2].texCoord, 0.0f, 50.0f);
                            vec2_set((float*)&ground_vertexBuffer[3].texCoord, 0.0f, 0.0f);
                            ground_indexBuffer[0] = 0;
                            ground_indexBuffer[1] = 1;
                            ground_indexBuffer[2] = 2;
                            ground_indexBuffer[3] = 2;
                            ground_indexBuffer[4] = 3;
                            ground_indexBuffer[5] = 0;

                            vec3_set((float*)&wall_vertexBuffer[0].position, -2.5f, 5.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[1].position, -2.5f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[2].position, -2.5f, 0.0f, -50.0f);
                            vec3_set((float*)&wall_vertexBuffer[3].position, -2.5f, 5.0f, -50.0f);
                            vec3_set((float*)&wall_vertexBuffer[0].normal, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[1].normal, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[2].normal, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[3].normal, 1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[0].tangent, 0.0f, 0.0f, -1.0f);
                            vec3_set((float*)&wall_vertexBuffer[1].tangent, 0.0f, 0.0f, -1.0f);
                            vec3_set((float*)&wall_vertexBuffer[2].tangent, 0.0f, 0.0f, -1.0f);
                            vec3_set((float*)&wall_vertexBuffer[3].tangent, 0.0f, 0.0f, -1.0f);
                            vec2_set((float*)&wall_vertexBuffer[0].texCoord, 0.0f, 5.0f);
                            vec2_set((float*)&wall_vertexBuffer[1].texCoord, 0.0f, 0.0f);
                            vec2_set((float*)&wall_vertexBuffer[2].texCoord, 50.0f, 0.0f);
                            vec2_set((float*)&wall_vertexBuffer[3].texCoord, 50.0f, 5.0f);
                            wall_indexBuffer[0] = 0;
                            wall_indexBuffer[1] = 1;
                            wall_indexBuffer[2] = 2;
                            wall_indexBuffer[3] = 2;
                            wall_indexBuffer[4] = 3;
                            wall_indexBuffer[5] = 0;
                            vec3_set((float*)&wall_vertexBuffer[4].position, 2.5f, 5.0f, -50.0f);
                            vec3_set((float*)&wall_vertexBuffer[5].position, 2.5f, 0.0f, -50.0f);
                            vec3_set((float*)&wall_vertexBuffer[6].position, 2.5f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[7].position, 2.5f, 5.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[4].normal, -1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[5].normal, -1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[6].normal, -1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[7].normal, -1.0f, 0.0f, 0.0f);
                            vec3_set((float*)&wall_vertexBuffer[4].tangent, 0.0f, 0.0f, 1.0f);
                            vec3_set((float*)&wall_vertexBuffer[5].tangent, 0.0f, 0.0f, 1.0f);
                            vec3_set((float*)&wall_vertexBuffer[6].tangent, 0.0f, 0.0f, 1.0f);
                            vec3_set((float*)&wall_vertexBuffer[7].tangent, 0.0f, 0.0f, 1.0f);
                            vec2_set((float*)&wall_vertexBuffer[4].texCoord, 0.0f, 5.0f);
                            vec2_set((float*)&wall_vertexBuffer[5].texCoord, 0.0f, 0.0f);
                            vec2_set((float*)&wall_vertexBuffer[6].texCoord, 50.0f, 0.0f);
                            vec2_set((float*)&wall_vertexBuffer[7].texCoord, 50.0f, 5.0f);
                            wall_indexBuffer[6] = 4;
                            wall_indexBuffer[7] = 5;
                            wall_indexBuffer[8] = 6;
                            wall_indexBuffer[9] = 6;
                            wall_indexBuffer[10] = 7;
                            wall_indexBuffer[11] = 4;

                            mesh_init(ground.mesh, &attribLocations, 4, 6, ground_vertexBuffer, ground_indexBuffer);
                            mesh_init(wall.mesh, &attribLocations, 8, 12, wall_vertexBuffer, wall_indexBuffer);
                            mesh_genCube(cube.mesh, &attribLocations);
                        }
                        else
                        {
                            printf("Failed to initialize GLEW.\n");
                        }
                    }
                    else
                    {
                        printf("Failed to enable the rendering context.\n");
                    }
                }
                else
                {
                    printf("Failed to create a rendering context.\n");
                }
            }
            else
            {
                printf("Failed to set the generated pixel format.\n");
            }
        }
        else
        {
            printf("Failed to generate a suitable pixel format.\n");
        }
    }
    else
    {
        printf("Failed to create a device context.\n");
    }
}

void resize(HWND window, WORD width_client, WORD height_client)
{
    player.view.aspect = (float)width_client / (float)height_client;
    glViewport(0, 0, width_client, height_client);
    InvalidateRect(window, NULL, FALSE);
}

void keyDown(HWND window, WPARAM key, LPARAM extra)
{
    switch (key)
    {
        case VK_ESCAPE:

            DestroyWindow(window);
            break;

        case 'W':

            keysPressed.forward = TRUE;
            break;

        case 'A':

            keysPressed.left = TRUE;
            break;

        case 'S':

            keysPressed.backward = TRUE;
            break;

        case 'D':

            keysPressed.right = TRUE;
            break;

        case 'C':

            keysPressed.crouch = TRUE;
            break;

        case VK_SHIFT:

            keysPressed.run = TRUE;
            break;

        case VK_SPACE:

            player_jump(&player);
            break;
    }

    player_calcVelocity(&player, &keysPressed);
}

void keyUp(HWND window, WPARAM key, LPARAM extra)
{
    switch (key)
    {
        case 'W':

            keysPressed.forward = FALSE;
            break;

        case 'A':

            keysPressed.left = FALSE;
            break;

        case 'S':

            keysPressed.backward = FALSE;
            break;

        case 'D':

            keysPressed.right = FALSE;
            break;

        case 'C':

            keysPressed.crouch = FALSE;
            break;

        case VK_SHIFT:

            keysPressed.run = FALSE;
            break;
    }

    player_calcVelocity(&player, &keysPressed);
}

void mouseMove(HWND window, WPARAM keys, int x, int y)
{
    RECT client;
    POINT clientCenter; // previous cursor
    LONG width;
    LONG height;

    GetClientRect(window, &client);
    width = client.right - client.left;
    height = client.bottom - client.top;
    clientCenter.x = width >> 1;
    clientCenter.y = height >> 1;

    // if cursor is not in the center of the screen
    // i.e.: if moved
    if (!(x == clientCenter.x &&
          y == clientCenter.y))
    {
        player_calcRotation(&player,
                            x - clientCenter.x,
                            y - clientCenter.y,
                            (float)width / (float)height);

        // recalc velocity vector
        player_calcVelocity(&player, &keysPressed);

        // then set cursor back to center of client
        ClientToScreen(window, &clientCenter);
        SetCursorPos(clientCenter.x, clientCenter.y);
    }
}

void render()
{
    static float modelMatrix[16];       // modelWorld
    static float viewMatrix[16];        // worldView
    static float projectionMatrix[16];  // viewClip
    static float angle = 0.0f;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

    // init matrices
    player_loadProjection(&player, projectionMatrix);
    player_loadView(&player, viewMatrix);
    mglmLoadIdentity(modelMatrix);

    // lights
    vec4_setv(light.position, lightPos);
    light_use(&light, viewMatrix);

    // draw
    mgluUpdateMatrices(modelMatrix, viewMatrix, projectionMatrix);
    object_draw(&ground);
    object_draw(&wall);

    mglmTranslate(modelMatrix, 0.0f, 2.0f, -10.0f);
    mglmRotateY(modelMatrix, angle);
    mgluUpdateMatrices(modelMatrix, viewMatrix, projectionMatrix);
    object_draw(&cube);

    glFlush();

    lightPos[2] -= 0.01f;
    angle += 1.0f;
}

void update(HWND window, WPARAM wParam, LPARAM lParam)
{
    checkErrors(window, __LINE__);

    player_collision(&player);
    player_step(&player);
    InvalidateRect(window, NULL, FALSE);
}

void destroy(HWND window)
{
    HDC dc = wglGetCurrentDC();
    HGLRC rc = wglGetCurrentContext();

    object_destroy(&ground);
    object_destroy(&wall);

    if (dc && rc)
    {
        wglMakeCurrent(dc, NULL);
        wglDeleteContext(rc);
    }

    if (dc)
    {
        ReleaseDC(window, dc);
    }

    if (ANIMATION)
    {
        KillTimer(window, 0);
    }
                                
    // posts WM_QUIT message
    // closes thread with exit value: 0
    PostQuitMessage(0);
}

void grid(float radius)
{
    float i;

    glBegin(GL_LINES);
    
    for (i = -radius; i < radius; ++i)
    {
        // longitudinal
        glVertex4f(i, 0.0f, radius, 1.0f);
        glVertex4f(i, 0.0f, -radius, 1.0f);
        // latitudinal
        glVertex4f(-radius, 0.0f, i, 1.0f);
        glVertex4f(radius, 0.0f, i, 1.0f);
    }

    glEnd();
}

static void checkErrors(HWND window, int lineNumber)
{
    int errorCode;
    char buffer[64];

    if (errorCode = glGetError())
    {
        ShowCursor(TRUE);
        mglErrorText(buffer, sizeof(buffer), errorCode);
        MessageBox(window, buffer, "Error", MB_OK | MB_ICONERROR);
        ShowCursor(FALSE);
    }
}

void mglErrorText(char* buffer, size_t size, GLenum errorCode)
{
    switch (errorCode)
    {
    case GL_NO_ERROR:

        *buffer = L'\0';
        break;

    case GL_INVALID_ENUM:

        strcpy_s(buffer, size, "GL_INVALID_ENUM");
        break;

    case GL_INVALID_VALUE:

        strcpy_s(buffer, size, "GL_INVALID_VALUE");
        break;

    case GL_INVALID_OPERATION:

        strcpy_s(buffer, size, "GL_INVALID_OPERATION");
        break;

    case GL_STACK_OVERFLOW:

        strcpy_s(buffer, size, "GL_STACK_OVERFLOW");
        break;

    case GL_STACK_UNDERFLOW:

        strcpy_s(buffer, size, "GL_STACK_UNDERFLOW");
        break;

    case GL_OUT_OF_MEMORY:

        strcpy_s(buffer, size, "GL_OUT_OF_MEMORY");
        break;

    default:

        sprintf_s(buffer, size, "Error: %u", errorCode);
    }
}