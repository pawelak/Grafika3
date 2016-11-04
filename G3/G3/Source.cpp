/*************************************************************************************/
//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rzednych
/*************************************************************************************/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <math.h>
#include "Source.h"
#include <iomanip>

using namespace std;


const int liczbaPodzialow = 41;
typedef float point3[3];
point3 tab[liczbaPodzialow+1][liczbaPodzialow+1];	


int u = 0, v = 1;
char model = 1;
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
float speed = 0.05;
point3 color = { 1.0, 1.0, 1.0 };


/*************************************************************************************/
// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

void pisz()
{
	for (int i = 0; i < liczbaPodzialow; i++)
	{
		for (int j = 0; j < liczbaPodzialow; j++)
		{
			cout << setw(5) << setprecision(3) << tab[i][j][0] << " ";
			cout << setw(5) << setprecision(3) << tab[i][j][1] << " ";
			cout << setw(5) << setprecision(3) << tab[i][j][2] << " ";
			cout << " | " << endl;
		}
		cout << endl << endl;
	}
	
}

void Axes(void)
{
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz�tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}
void fillMatrix()
{
	for (int i = 0; i < liczbaPodzialow; i++)
	{
		for (int j = 0; j < liczbaPodzialow; j++)
		{
			tab[i][j][0] = ((float)1 / (float)liczbaPodzialow)*i;
			tab[i][j][1] = ((float)1 / (float)liczbaPodzialow)*j;
			tab[i][j][2] = 0;
		}
	}
	cout << endl << endl;
}

void transformMatrix()
{
	int i=0, j=0;
	float uL;
	for (i = 0; i < liczbaPodzialow; i++)
	{
		for (j = 0; j < liczbaPodzialow; j++)
		{
			if (j == 0)uL = tab[i][j][0];
			float vL = tab[i][j][1];

			tab[i][j][0] = (-90 * pow(uL, 5) + (225 * pow(uL, 4)) - (270 * pow(uL, 3)) + (180 * pow(uL, 2)) - (45 * uL))*cos(M_PI*vL);
			tab[i][j][1] = 160 * pow(uL, 4) - 320 * pow(uL, 3) + 160 * pow(uL, 2);
			tab[i][j][2] = (-90 * pow(uL, 5) + (225 * pow(uL, 4)) - (270 * pow(uL, 3)) + (180 * pow(uL, 2)) - (45 * uL))*sin(M_PI*vL);
		}
	}
	//pisz(); //sprawdzenie pozycji punkt�w w macierzy 
}

void paint()
{

	glPointSize(1); // podajemy wielko�� punktu
	glColor3f(1, 0, 0);

	switch (model)
	{
		case '1':
	{

		for (int i = 0; i < liczbaPodzialow; i++)
		{
			glColor3f(1, 0, 0);
			for (int j = 0; j < liczbaPodzialow; j++)
			{
				glBegin(GL_POINTS);
				glVertex3fv(tab[i][j]);
				glEnd();
			}
		}
		break;
	}
	case '2':
	{

		for (int i = 0; i < liczbaPodzialow; i++)
		{
			glColor3f(1, 0, 0);
			for (int j = 0; j < liczbaPodzialow-1; j++)
			{
				glBegin(GL_LINES); //poziom
				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i][j + 1]);

				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i+1][j]);

				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i + 1][j+1]);

				glEnd();



			}
			glBegin(GL_LINES); //tu uzupe�niem brakuj�ce elementy kt�rych nie dosrysowa�o przy tworzeniu jajka

			glVertex3fv(tab[i][liczbaPodzialow-1]); //poziom uzupe�nienie
			glVertex3fv(tab[liczbaPodzialow-i][0]);

			glVertex3fv(tab[i][liczbaPodzialow-1]); //pion uzupe�nienie 
			glVertex3fv(tab[i+1][liczbaPodzialow-1]);

			glVertex3fv(tab[i][liczbaPodzialow - 1]); //poziom uzupe�nienie
			glVertex3fv(tab[liczbaPodzialow - i-1][0]);

			glEnd();
		}


		break;
	}
	case '3':
	{
		glColor3fv(color);
		for (int i = 0; i < liczbaPodzialow; i++) 
		{
			for (int j = 0; j < liczbaPodzialow; j++)
			{
				//W jedna strone
				glBegin(GL_TRIANGLES);

				glVertex3fv(tab[i][j + 1]);
				glVertex3fv(tab[i + 1][j]);
				glVertex3fv(tab[i + 1][j + 1]);
				glEnd();

				//W druga strone
				glBegin(GL_TRIANGLES);
				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i + 1][j]);
				glVertex3fv(tab[i][j + 1]);
				glEnd();
			}
		}
		break;
	}
	case '4':
	{
		glColor3fv(color);
		for (int i = 0; i < liczbaPodzialow; i++)
		{
			for (int j = 0; j < liczbaPodzialow; j++)
			{
				glBegin(GL_POLYGON);
				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i][j+1]);
				glVertex3fv(tab[i+1][j+1]);
				glVertex3fv(tab[i+1][j]);
				glEnd();
			}
		}
		break;
	}
	case '5':
	{
		{
			srand((unsigned)time(NULL));
			for (int i = 0; i < liczbaPodzialow; i++)
			{
				for (int j = 0; j < liczbaPodzialow; j++)
				{
					//W jedna strone
					glBegin(GL_TRIANGLES);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i][j + 1]);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i + 1][j]);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i + 1][j + 1]);
					glEnd();

					//W druga strone
					glBegin(GL_TRIANGLES);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i][j]);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i + 1][j]);
					glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
					glVertex3fv(tab[i][j + 1]);
					glEnd();
				}
			}
			break;
		}
	}
	case '6':
	{
		glColor3fv(color);
		for (int i = 0; i < liczbaPodzialow; i++)
		{
			for (int j = 0; j < liczbaPodzialow; j++)
			{
				int r = rand()% +3;
				color[r] = (rand() % 100)*0.01;
				glBegin(GL_POLYGON);
				glColor3fv(color);
				glVertex3fv(tab[i][j]);
				glColor3fv(color);
				glVertex3fv(tab[i][j + 1]);
				glColor3fv(color);
				glVertex3fv(tab[i + 1][j + 1]);
				glColor3fv(color);
				glVertex3fv(tab[i + 1][j]);
				glEnd();
			}
		}
		break;
	}


	default:
		break;
	}

	/*

			if (model == 2)
			{
				glBegin(GL_LINES); //pion
				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i][j+1]);
				glEnd();

				glBegin(GL_LINES); //poziom
				glVertex3fv(tab[i][j]);
				glVertex3fv(tab[i][j]);
				glEnd();

				glBegin(GL_LINES);
				if (j + 1 < liczbaPodzialow && i + 1 < liczbaPodzialow)
				{
					glVertex3fv(tab[i + 1][j]);
					glVertex3fv(tab[i][j + 1]);
				}

				glColor3f(0, 1, 0);
				glVertex3fv(tab[liczbaPodzialow][4]);
				glVertex3fv(tab[liczbaPodzialow-1][4]);
				glColor3f(1, 0, 0);
				glEnd();*/
				/*}
				if (model == 3)
				{
					for (int i = 0; i < liczbaPodzialow; i++)
					{
						for (int j = 0; j < liczbaPodzialow; j++)
						{
							if (i + 1 < liczbaPodzialow && j+1 <liczbaPodzialow)
							{
								glBegin(GL_TRIANGLES);
								glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i][j]);
								glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i+1][j]);
								glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i + 1][j + 1]);
								glEnd();

								glBegin(GL_TRIANGLES);*/

								/*glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i][j]);
								glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i][j+1]);
								glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
								glVertex3fv(tab[i + 1][j + 1]);

								glColor3f(0.01,0.8,0.1);
								glVertex3fv(tab[i][j]);
								glVertex3fv(tab[i][j + 1]);
								glVertex3fv(tab[i + 1][j + 1]);

								glEnd();
								*/

}


/*************************************************************************************/
// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba 
// przerysowa� scen�)

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	 
	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glTranslatef(0, -5, 0);



	//glRotated(20.0, 1.0, 0.0, 0.0);  // Obr�t o 60 stopni
	
	
	paint();
	
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

	glutSwapBuffers();
	//
}

/*************************************************************************************/
// Funkcja ustalaj�ca stan renderowania

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny
	fillMatrix();
	transformMatrix();
}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)
		glOrtho(-12, 12, -12 / AspectRatio, 12 / AspectRatio, 20.0, -10.0);
	else
		glOrtho(-15, 15, -15 / AspectRatio, 15 / AspectRatio, 20.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   
	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}
/*************************************************************************************/
// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli

void keys(unsigned char key, int x, int y)
{
	if (key == '1') model = '1';
	if (key == '2') model = '2';
	if (key == '3') model = '3';
	if (key == '4') model = '4';
	if (key == '5') model = '5';
	if (key == '6') model = '6';
	if (key == 'r')
	{
		color[0] += 0.05;
		if (color[0] > 1)color[0] = 0;
	}
	if (key == 'g')
	{
		color[1] += 0.05;
		if (color[1] > 1)color[1] = 0;
	}
	if (key == 'b')
	{
		color[2] += 0.05;
		if (color[2] > 1)color[2] = 0;
	}

	RenderScene(); // przerysowanie obrazu sceny
}

void spinEgg()
{

	theta[0] -= speed;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= speed;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= speed;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}



void main(void)
{
	


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

	glutKeyboardFunc(keys);
	glutIdleFunc(spinEgg);

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem 
	// gdy zajdzie potrzba przeryswania okna 


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna      
	MyInit();
	
	

	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
/*************************************************************************************/




