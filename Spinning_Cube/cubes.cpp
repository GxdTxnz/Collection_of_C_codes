/* Этот код является доработкой (переделкой) оригинального кода:
* https://github.com/servetgulnaroglu/cube.c
* Видео автора кода:
* https://www.youtube.com/watch?v=p09i_hoFdd0
* Изменения:
* - отрисовывается один куб по центру экрана;
* - размер куба меняется в зависимости от размера окна терминала;
* - переписан на C++;
*/


#include <cmath>
#include <ncurses.h>
#include <vector>
#include <csignal>
#include <unistd.h>

class CubeRenderer {
private:
  float A = 0, B = 0, C = 0;
  float cubeWidth;
  float horizontalOffset = 0;
  float K1 = 40;
  float incrementSpeed = 0.6;
  
  int width, height;
  int distanceFromCam = 100;

  std::vector<float> zBuffer;
  std::vector<char> buffer;

  void calculateTerminalSize()
  {
    getmaxyx(stdscr, height, width);
    cubeWidth = height / 2.5;
    zBuffer.resize(width * height, 0);
    buffer.resize(width * height, ' ');
  }

  float calculateX(int i, int j, int k) const
  {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
  }

  float calculateY(int i, int j, int k) const
  {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
  }

  float calculateZ(int i, int j, int k) const
  {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
  }

  void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch)
  {
    float x = calculateX(cubeX, cubeY, cubeZ);
    float y = calculateY(cubeX, cubeY, cubeZ);
    float z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
    float ooz = 1 / z;

    int xp = static_cast<int>(width / 2 + horizontalOffset + K1 * ooz * x * 2);
    int yp = static_cast<int>(height / 2 + K1 * ooz * y);
    int idx = xp + yp * width;

    if (idx >= 0 && idx < width * height)
    {
      if (ooz > zBuffer[idx])
      {
        zBuffer[idx] = ooz;
        buffer[idx] = ch;
      }
    }
  }

public:
  CubeRenderer()
  {
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    calculateTerminalSize();
  }

  ~CubeRenderer()
  {
    endwin();
  }

  void renderFrame()
  {
    calculateTerminalSize();

    std::fill(buffer.begin(), buffer.end(), ' ');
    std::fill(zBuffer.begin(), zBuffer.end(), 0);

    for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
    {
      for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
      {
        calculateForSurface(cubeX, cubeY, -cubeWidth, '.');
        calculateForSurface(cubeWidth, cubeY, cubeX, '$');
        calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
        calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
        calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
        calculateForSurface(cubeX, cubeWidth, cubeY, '+');
      }
    }

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        int idx = x + y * width;
        mvaddch(y, x, buffer[idx]);
      }
    }

    A += 0.05;
    B += 0.05;
    C += 0.01;
    refresh();
  }
};

bool running = true;

void handleSignal(int)
{
  running = false;
}

int main()
{
  signal(SIGINT, handleSignal);
  CubeRenderer renderer;

  while (running)
  {
    renderer.renderFrame();
    usleep(16000);
  }
  return 0;
}
