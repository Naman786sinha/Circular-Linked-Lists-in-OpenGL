//  CG Project###################################################
#pragma warning(disable:4996)
#include<Windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
/*
#ifdef debug
#define LOG(x) printf("%s\n",x);
#else
#define LOG(x)
#endif //
*/

//To draw the Linked List, these are needed
int x = 110, temp1 = 200;
int y = 100, count = 5;
int fullyTraversed = 0, call = 0;
int choice = 0, temp2 = 0, flag = 0;
int  w = 0, dup = 0;
//To write the information and explanation, these are needed
int info[50] = { 10,25,56,78,59 };//The nodes will have these as the contents of info field
int link[50] = { 4,6,9,12,1 };//The nodes will have these as the contents of link field

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, 1, -1);
	//glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int state = 0;///////////////

void text(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i]);
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, a[i]);
	}
}

void text1(char *a, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; a[i] != '\0'; i++) {
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i]);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, a[i]);
	}
}

void write()//Called in display
{
	int pos = x + 40;
	char typeinfo[5];
	char typelink[5];
	char address[3];//To write the address at the bottom of the already drawn nodes
	for (int i = 0; i < count; i++)
	{
		itoa(info[i], typeinfo, 10);
		itoa(link[i], typelink, 10);
		//typeinfo = atoi(info[i]);
		text(typeinfo, pos, y);//To write on the info field
		text(typelink, pos + 40, y);//To write on the link field
		//Values of typelink and typeinfo will keep changing after every iteraton
		if (i == 0)
			itoa(link[count - 1], address, 10);
		else
			itoa(link[i - 1], address, 10);
		text(address, pos + 30, y - 30);//To write 30 points below the list and pos+30 is to write in the center of the node....pos already more 
		pos = pos + 110;//For the next node,all this must be repeated
	}
}

void draw_list(int x, int y)//From 30-70 it draws a part of the list and the it is called again from 70-110 for remainimg part of the list
{//Called in multiple 
	glBegin(GL_POLYGON);//Draws the box only one-half at a time
	glVertex2f(x + 70, y + 20);
	glVertex2f(x + 30, y + 20);
	glVertex2f(x + 30, y);
	glVertex2f(x + 70, y);
	glEnd();
	glFlush();
}

void draw_arrow(int x, int y)//From 0-30 in x it draws the arrow
{//Called in multiple
	glBegin(GL_LINES);
	glVertex2f(x, y + 10);
	glVertex2f(x + 20, y + 10);
	glEnd();
	glFlush();
	glColor3f(1.0, 0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x + 20, y + 15);
	glVertex2f(x + 20, y + 5);
	glVertex2f(x + 30, y + 10);
	glEnd();
	glFlush();
}

void multiple()//Called in display 
{
	draw_arrow(x, y);//First draw the arrow from 0-30
	glColor3f(0, 1.0, 0);
	draw_list(x, y);//Draw the first half of the list
	glColor3f(1.0, 1.0, 0);
	draw_list(x + 40, y);//Draw the second half of the list by adding 40 to x
	glColor3f(1.0, 0, 0);
}

void pointer(int m, int n)//Called in timer
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(m + 70, n + 100);
	glVertex2f(m + 70, n + 60);
	glVertex2f(m + 80, n + 60);
	glVertex2f(m + 70, n + 50);
	glVertex2f(m + 60, n + 60);
	glVertex2f(m + 70, n + 60);
	glColor3f(0, 1, 1);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);//Draws the part where text gets printed
	glVertex2f(x - 100, y + 200);
	glVertex2f(x + 500, y + 200);
	glVertex2f(x + 500, y + 230);
	glVertex2f(x - 100, y + 230);
	glEnd();
	glColor3f(0, 1, 0);
	text1("Traversing the Circular Linked List", x + 50, y + 210);
	glColor3f(1, 0, 0);
	glFlush();
	glutSwapBuffers();
}

void timer(int z, int w)//Called in traverse
{
	glPushMatrix();
	pointer(z, y);
	glTranslatef(110, 0, 0);
	pointer(z, y + w);
	glPopMatrix();
}

void delay()//Called in traverse
{
	for (int s = 0; s < 10000; s++)
		for (int t = 0; t < 15000; t++);
}

void traverse()//Called in comments to indicate the affected node in case 15
{
	if (fullyTraversed)
		return;
	if (state == 0)
		w = 0;
	else if (state == 1)
	{
		w = 100;
		glutPostRedisplay();
	}
	else
	{
		state = 0;
		fullyTraversed = 1;
		return;
	}
	dup = x - 110;
	for (int j = 0; j < count; j++)
	{
		if (state == 2)
			break;
		//check = 0;
		delay();
		//glColor3f(0, 1, 0);
		//text1("Traversing the Circular Linked List", x + 140, y + 210);
		glColor3f(1, 0, 0);
		glFlush();
		timer(dup, w);
		delay();
		//printf("%d\n", j);
		dup += 110;
		if (j == count - 1)
		{
			state++;
			traverse();
		}
	}
}

void draw_box(int p, int q)//Called in comments to draw the comment box the affected node except case 15
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(p - 80, q + 170);
	glVertex2f(p + 260, q + 170);
	glVertex2f(p + 260, q + 110);
	glVertex2f(p + 100, q + 110);
	glVertex2f(p + 70, q + 50);//To draw the pointed end for indication
	glVertex2f(p + 80, q + 110);
	glVertex2f(p - 80, q + 110);
	glColor3f(0, 1, 1);
	glEnd();
}

void print_empty()
{
	text1("List is Empty!!", x + 140, y + 150);
	glFlush();
}

void comments()//Called in display function
{
	switch (choice)
	{
		int r;
	case 1:
		glColor3f(0, 1.0, 0);
		text1("Adding a node at the beginning of the List", x + 110, y + 210);
		glColor3f(0.5, 0.5, 0.5);
		draw_box(x, y);
		text1("Node added at the beginning of the list", x - 70, y + 150);
		glFlush();
		break;

	case 2:
		glColor3f(0, 1.0, 0);
		text1("Adding a node at the end of the List", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x + (count - 1) * 110;
		draw_box(r, y);
		text1("Node added at the end of the list", r - 70, y + 150);
		glFlush();
		break;

	case 3:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node from the beginning of the List", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x - 110;
		if (count <= 0)
		{
			print_empty();
			break;
		}
		draw_box(r, y);
		text1("Node deleted from beginning of list", r - 70, y + 150);
		glFlush();
		break;

	case 4:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node from the end of the List", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x + count * 110;
		if (count <= 0)
		{
			print_empty();
			break;
		}
		draw_box(r, y);
		text1("Node deleted from end of list", r - 70, y + 150);
		glFlush();
		break;

	case 5:
		glColor3f(0, 1.0, 0);
		text1("Adding a node before specified node by Content", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x + temp2 * 110;
		draw_box(r, y);
		text1("Node added before specified content", r - 70, y + 150);
		glFlush();
		break;

	case 6:
		glColor3f(0, 1.0, 0);
		text1("Adding a node before specified node by Address", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x + temp2 * 110;
		draw_box(r, y);
		text1("Node added before specified address", r - 70, y + 150);
		glFlush();
		break;

	case 7:
		glColor3f(0, 1.0, 0);
		text1("Adding a node after specified node by Content", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x + (temp2 + 1) * 110;
		draw_box(r, y);
		text1("Node added after specified content", r - 70, y + 150);
		glFlush();
		break;

	case 8:
		glColor3f(0, 1.0, 0);
		text1("Adding a node after specified node by Address", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		if (temp2 == count - 2)
			r = x + 110;
		else
			r = x + (temp2 + 2) * 110;
		draw_box(r, y);
		text1("Node added after specified address", r - 70, y + 150);
		glFlush();
		break;

	case 9:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node before a specified node by Content", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		if (temp2 == 0)
			r = x - 50 + count * 110;
		else
			r = x - 50 + (temp2 - 1) * 110;
		draw_box(r, y);
		text1("Node deleted before specified content", r - 70, y + 150);
		glFlush();
		break;

	case 10:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node before a specified node by Address", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		r = x - 50 + (temp2) * 110;
		draw_box(r, y);
		text1("Node deleted before specified address", r - 70, y + 150);
		glFlush();
		break;

	case 11:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node after specified node by Content", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		if (temp2 == count)
			r = x - 50;
		else
			r = x - 50 + (temp2 + 1) * 110;
		draw_box(r, y);
		text1("Node deleted after specified content", r - 70, y + 150);
		glFlush();
		break;

	case 12:
		glColor3f(0, 1.0, 0);
		text1("Deleting a node after specified node by Address", x + 110, y + 210);
		glColor3f(1.0, 0, 0);
		if (temp2 == count)
			r = x - 50 + 110;
		else if (temp2 == count - 1)
			r = x - 50;
		else
			r = x - 50 + (temp2 + 2) * 110;
		draw_box(r, y);
		text1("Node deleted after specified address", r - 70, y + 150);
		glFlush();
		break;

	case 13:
		glColor3f(0, 1.0, 0);
		text1("Searching for a node in the List by Content", x + 110, y + 210);
		if (flag == 1)
		{
			glColor3f(1.0, 0, 0);
			r = x + (temp2) * 110;
			draw_box(r, y);
			text1("Searched node found here!!!", r - 70, y + 150);
		}
		glFlush();
		break;

	case 14:
		glColor3f(0, 1.0, 0);
		text1("Searching for a node in the List by Address", x + 110, y + 210);
		if (flag == 1)
		{
			glColor3f(1.0, 0, 0);
			r = x + (temp2) * 110;
			draw_box(r, y);
			text1("Searched node found here!!!", r - 70, y + 150);
		}
		glFlush();
		break;

	case 15:
		//glutSetWindow(call);
		//printf("Traversing the Circular Linked List\n");
		glutIdleFunc(traverse);
		traverse();
		break;

	case 16:
		exit(0);

	default:
		glutPostRedisplay();
	}
}

void display()//Called in common
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5, 0, 0.5, 1);
	text("Circular Linked List", x + 190, y + 250);
	comments();
	if (count <= 0)
	{
		printf("The count is %d\n", count);
	}
	else
	{
		glPushMatrix();//very important
		for (int i = 0; i < count; i++)
		{
			multiple();//call as many times as we want to draw an rrow and a node
			glTranslatef(110, 0.0, 0.0);
		}
		//Drawing connections between first and last node
		x = temp1;
		glBegin(GL_LINES);
		glVertex2f(x, y + 10);
		glVertex2f(x + 20, y + 10);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x + 20, y + 10);
		glVertex2f(x + 20, y + 40);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x + 20, y + 40);
		float p;//As a temporary local variable
		p = x + 20 - (count) * 110;
		glVertex2f(p - 20, y + 40);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(p - 20, y + 40);
		glVertex2f(p - 20, y + 10);
		glEnd();
		glPopMatrix();//very important
		write();//Write onto the blank nodes
	}
	glutSwapBuffers();
}

void common()//Called in MENU for all cases except case 15
{
	glutDisplayFunc(display);
	glutPostRedisplay();
	glutReshapeFunc(myReshape);
}

int ele()//Called in MENU 
{
	int a = 0;
	printf("Enter the element to be inserted in the new node\n");
	scanf("%d", &a);
	return a;
}

int adr()//Called in MENU 
{
	int b = 0, fl = 0;
	b = rand() % 100 + 1;
	for (int i = 0; i < count - 1; i++)
	{
		if (b == link[i])
		{
			fl = 1;
			break;
		}


	}
	if (fl == 1)
		b = adr();
	return b;
}

void initcount()//Called in MENU
{
	if (count < 0)
		count = 0;
}

void MENU(int ch)//Called in the add_menu function
{
	int newinfo, newlink, specnode = 0;//For taking new content,address and node telling before or after
	int reassign = 0;//Temporary variable
	switch (ch)
	{
		initcount();
	case 1://ADD at the BEGINNING
		count++;
		choice = 1;
		newinfo = ele();
		newlink = adr();
		reassign = link[count - 2];//Extracts the link of the last node pointing to the first node
		for (int i = count - 1; i > 0; i--)
		{
			info[i] = info[i - 1];
			link[i - 1] = link[i - 2];
		}
		info[0] = newinfo;//Assign info entered
		link[0] = reassign;//Assign the extracted link field to the first node so the it points to the second node....Add in Beginning!
		link[count - 1] = newlink;//Assign last node to point to the first newly added node
		common();
		break;

	case 2://ADD at the END
		count++;
		choice = 2;
		//add_menu();
		//y = y - 100;
		newinfo = ele();
		newlink = adr();
		info[count - 1] = newinfo;
		reassign = link[count - 2];
		link[count - 2] = newlink;
		link[count - 1] = reassign;
		common();
		break;

	case 3://DELETE from the BEGINNING
		count--;
		choice = 3;
		reassign = link[0];
		for (int i = 0; i <= count; i++)
		{
			info[i] = info[i + 1];
			link[i] = link[i + 1];
		}
		link[count - 1] = reassign;
		common();
		break;

	case 4://DELETE from the END
		count--;
		choice = 4;
		reassign = link[count];
		link[count - 1] = reassign;
		info[count] = 0;
		common();
		break;

	case 5://ADD BEFORE a specified node BY CONTENT 
		count++;
		choice = 5;
		do
		{
		A:
			flag = 0;
			printf("Enter the element before which the new node must be inserted\n");
			scanf("%d", &specnode);
			newinfo = ele();
			newlink = adr();
			for (int i = 0; i <= count - 2; i++)
			{
				if (info[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 == 0)//If tried to enter before first node,copy same code as that of add at the beginning
				{
					reassign = link[count - 2];
					for (int i = count - 1; i > 0; i--)
					{
						info[i] = info[i - 1];
						link[i - 1] = link[i - 2];
					}
					info[0] = newinfo;
					link[0] = reassign;
					link[count - 1] = newlink;
				}
				else
				{
					for (int j = count - 1; j > temp2; j--)
					{
						info[j] = info[j - 1];
						link[j] = link[j - 1];
					}
					link[temp2] = link[temp2 - 1];
					info[temp2] = newinfo;
					link[temp2 - 1] = newlink;
				}
				common();
				break;
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto A;
			}
		} while (flag != 1);
		break;

	case 6://ADD BEFORE a specified node BY ADDRESS 
		count++;
		choice = 6;
		do
		{
		B:
			flag = 0;
			printf("Enter the address before which the new node must be inserted\n");
			scanf("%d", &specnode);
			newinfo = ele();
			newlink = adr();
			for (int i = 0; i <= count - 2; i++)
			{
				if (link[i] == specnode)
				{
					temp2 = i + 1;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 - 1 == 0)//If tried to enter before first node,copy same code as that of add at the beginning
				{
					reassign = link[count - 2];
					for (int i = count - 1; i > 0; i--)
					{
						info[i] = info[i - 1];
						link[i - 1] = link[i - 2];
					}
					info[0] = newinfo;
					link[0] = reassign;
					link[count - 1] = newlink;
				}
				else
				{
					for (int j = count - 1; j > temp2; j--)
					{
						link[j] = link[j - 1];
						info[j] = info[j - 1];
					}
					link[temp2] = link[temp2 - 1];
					info[temp2] = newinfo;
					link[temp2 - 1] = newlink;
				}
				common();
				break;
			}
			else
			{
				printf("Ërror!!!!Please enter an existing ele!\n");
				goto B;
			}
		} while (flag != 1);
		break;

	case 7://ADD AFTER a specified node BY CONTENT 
		count++;
		choice = 7;
		do
		{
		C:
			flag = 0;
			printf("Enter the element after which the new node must be inserted\n");
			scanf("%d", &specnode);
			newinfo = ele();
			newlink = adr();
			for (int i = 0; i <= count - 2; i++)
			{
				if (info[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				for (int j = count - 1; j > temp2 + 1; j--)
				{
					info[j] = info[j - 1];
					link[j] = link[j - 1];
				}
				link[temp2 + 1] = link[temp2];
				info[temp2 + 1] = newinfo;
				link[temp2] = newlink;
				common();
				break;
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto C;
			}
		} while (flag != 1);
		break;

	case 8://ADD AFTER a specified node BY ADDRESS 
		count++;
		choice = 8;
		do
		{
		D:
			flag = 0;
			printf("Enter the address after which the new node must be inserted\n");
			scanf("%d", &specnode);
			newinfo = ele();
			newlink = adr();
			for (int i = 0; i < count - 1; i++)
			{
				if (link[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 == count - 2)
				{
					reassign = link[count - 2];//Code to add in the beginning
					for (int i = count - 1; i > 1; i--)
					{
						info[i] = info[i - 1];
						link[i - 1] = link[i - 2];
					}
					info[1] = newinfo;
					link[count - 1] = reassign;
					link[0] = newlink;
					common();
					break;
				}
				else
				{
					for (int j = count - 1; j > temp2 + 1; j--)
					{
						link[j] = link[j - 1];
						info[j] = info[j - 1];
					}
					reassign = link[temp2 + 1];
					info[temp2 + 2] = newinfo;
					link[temp2 + 1] = newlink;
					link[temp2 + 2] = reassign;
					common();
					break;
				}
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto D;
			}
		} while (flag != 1);
		break;

	case 9://DELETE BEFORE a specified node BY CONTENT 
		count--;
		choice = 9;
		do
		{
		E:
			flag = 0;
			printf("Enter the element before which the node must be deleted\n");
			scanf("%d", &specnode);
			for (int i = 0; i <= count; i++)
			{
				if (info[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 == 0)
				{
					reassign = link[count];
					link[count - 1] = reassign;
					info[count] = 0;
					common();
					break;
				}
				else
				{
					reassign = link[temp2 - 1];
					for (int j = temp2 - 1; j < count; j++)
					{
						info[j] = info[j + 1];
						link[j] = link[j + 1];
					}
					link[temp2 - 2] = reassign;
					common();
					break;
				}
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto E;
			}
		} while (flag != 1);
		break;

	case 10://DELETE BEFORE a specified node BY ADDRESS 
		count--;
		choice = 10;
		do
		{
		F:
			flag = 0;
			printf("Enter the address before which the node must be deleted\n");
			scanf("%d", &specnode);
			for (int i = 0; i <= count; i++)
			{
				if (link[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				reassign = link[temp2];
				for (int j = temp2; j < count; j++)
				{
					link[j] = link[j + 1];
					info[j] = info[j + 1];
				}
				link[temp2 - 1] = reassign;
				common();
				break;
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto F;
			}
		} while (flag != 1);
		break;

	case 11://DELETE AFTER a specified node BY CONTENT 
		count--;
		choice = 11;
		do
		{
		G:
			flag = 0;
			printf("Enter the element after which the node must be deleted\n");
			scanf("%d", &specnode);
			for (int i = 0; i <= count; i++)
			{
				if (info[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 == count)
				{
					reassign = link[0];
					for (int i = 0; i <= count; i++)
					{
						info[i] = info[i + 1];
						link[i] = link[i + 1];
					}
					link[count - 1] = reassign;
					common();
					break;
				}
				else
				{
					reassign = link[temp2 + 1];
					for (int j = temp2 + 1; j < count; j++)
					{
						info[j] = info[j + 1];
						link[j] = link[j + 1];
					}
					link[temp2] = reassign;
					common();
					break;
				}
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto G;
			}
		} while (flag != 1);
		break;

	case 12://DELETE AFTER a specified node BY ADDRESS 
		count--;
		choice = 12;
		do
		{
		H:
			flag = 0;
			printf("Enter the element after which the node must be deleted\n");
			scanf("%d", &specnode);
			for (int i = 0; i <= count; i++)
			{
				if (link[i] == specnode)
				{
					temp2 = i;
					flag = 1;
					break;
				}
				else
					continue;
			}
			if (flag == 1)
			{
				if (temp2 == count - 1)
				{
					reassign = link[0];
					for (int i = 0; i < count; i++)
					{
						link[i] = link[i + 1];
						info[i] = info[i + 1];
					}
					link[count - 1] = reassign;
					common();
					break;
				}
				else if (temp2 == count)
				{
					reassign = link[1];
					for (int i = 1; i < count; i++)
					{
						link[i] = link[i + 1];
						info[i] = info[i + 1];
					}
					link[0] = reassign;
					common();
					break;
				}
				else
				{
					reassign = link[temp2 + 2];
					for (int j = temp2 + 2; j < count; j++)
					{
						link[j] = link[j + 1];
						info[j] = info[j + 1];
					}
					link[temp2 + 1] = reassign;
					common();
					break;
				}
			}
			else
			{
				printf("Error!!!!Please enter an existing element!\n");
				goto H;
			}
		} while (flag != 1);
		break;

	case 13://Searching a node by content
		choice = 13;
		flag = 0;
		printf("Enter the element to be searched in the list\n");
		scanf("%d", &specnode);
		for (int i = 0; i < count; i++)
		{
			if (info[i] == specnode)
			{
				temp2 = i;
				flag = 1;
				break;
			}
			else
				continue;
		}
		if (flag == 1)
		{
			printf("Element found!!!\n");
			common();
		}
		else
			printf("Node not found!!!\n");
		break;

	case 14://Searching a node by address
		choice = 14;
		flag = 0;
		printf("Enter the address of the node to be searched in the list\n");
		scanf("%d", &specnode);
		for (int i = 0; i < count; i++)
		{
			if (link[i] == specnode)
			{
				if (i == count - 1)
					temp2 = 0;
				else
					temp2 = i + 1;
				flag = 1;
				break;
			}
			else
				continue;
		}
		if (flag == 1)
		{
			printf("Element found!!!\n");
			common();
		}
		else
			printf("Node not found!!!\n");
		break;

	case 15://Traversing the list
		choice = 15;
		if (fullyTraversed)
		{
			fullyTraversed = 0;
			break;
		}
		common();
		glutPostRedisplay();
		break;

	case 16://Exit
		exit(0);

	default:
		glutPostRedisplay();
	}
	glFlush();
}

void add_menu()//Called in the keys function
{
	int id4 = glutCreateMenu(MENU);//Adding a node before specified
	glutAddMenuEntry("Specify by content", 5);
	glutAddMenuEntry("Specify by address", 6);

	int id5 = glutCreateMenu(MENU);//Adding a node after specified
	glutAddMenuEntry("Specify by content", 7);
	glutAddMenuEntry("Specify by address", 8);

	int id6 = glutCreateMenu(MENU);//Deleting a node before specified
	glutAddMenuEntry("Specify by content", 9);
	glutAddMenuEntry("Specify by address", 10);

	int id7 = glutCreateMenu(MENU);//Deleting a node after specified
	glutAddMenuEntry("Specify by content", 11);
	glutAddMenuEntry("Specify by address", 12);

	int id8 = glutCreateMenu(MENU);//Searching a node
	glutAddMenuEntry("Search by content", 13);
	glutAddMenuEntry("Search by address", 14);

	int id2 = glutCreateMenu(MENU);//Adding a node
	glutAddSubMenu("Before a specified node", id4);
	glutAddSubMenu("After a specified node", id5);

	int id3 = glutCreateMenu(MENU);//Deleting a node
	glutAddSubMenu("Before a specified node", id6);
	glutAddSubMenu("After a specified node", id7);

	int id = glutCreateMenu(MENU);//For adding
	glutAddMenuEntry("At the beginning", 1);
	glutAddMenuEntry("At the end", 2);
	glutAddSubMenu("At specified position", id2);

	int id1 = glutCreateMenu(MENU);//For deleting
	glutAddMenuEntry("At the beginning", 3);
	glutAddMenuEntry("At the end", 4);
	glutAddSubMenu("At specified position", id3);

	glutCreateMenu(MENU);//Initial options
	glutAddSubMenu("ADD A NEW NODE", id);
	glutAddSubMenu("DELETE AN EXISTING NODE", id1);
	glutAddSubMenu("SEARCH A NODE", id8);
	glutAddMenuEntry("TRAVERSE THE LIST", 15);
	glutAddMenuEntry("EXIT", 16);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void keys(unsigned char key, int x, int y)//Called in initdisplay,creates menu and calles the add_menu then display!!!
{
	if (key == 's' || key == 'S')
	{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowPosition(300, 280);
		glutInitWindowSize(1000, 400);
		glutCreateWindow("Circular Linked List");
		add_menu();
		glutDisplayFunc(display);
		glutReshapeFunc(myReshape);
	}
}

void initdisplay()//Called in main,when S/s is pressed on this screen,window switches!!! 
{//From here the control goes to keys
	y = y + 70;//To display the contents above
	glClearColor(10 / 255, 100 / 255, 0 / 255, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	text("CIRCULAR LINKED LISTS", x + 190, y + 50);
	text("S", x + 300, y - 100);
	glColor3f(0, 1, 0);
	text1("Department of CSE", x + 260, y + 100);
	glColor3f(0, 0, 1);
	text("B.N.M Institute of Technology", x + 190, y + 150);
	glColor3f(0, 1, 0);
	text1("Name:", x, y - 50);
	text1("USN:", x, y - 70);
	glColor3f(1, 0, 0);
	text("By:", x, y - 20);
	text("Guide:", x + 500, y - 20);
	glColor3f(0, 0, 1);
	text1("NAMAN SINHA", x + 60, y - 50);
	text1("1BG16CS064", x + 60, y - 70);
	text1("Mrs. RANJANA CHAKRASALI", x + 500, y - 50);
	text1("Assistant Professor,Department of CSE", x + 500, y - 70);
	text("Press    key to start!", x + 240, y - 100);
	y = y - 70;
	glFlush();
	glutSwapBuffers();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(300, 280);
	glutInitWindowSize(1000, 400);
	call = glutCreateWindow("Circular Linked List");
	glutDisplayFunc(initdisplay);//First this display function will be called...
	glutKeyboardFunc(keys);//For going from start page to next page after pressing S os s
	glutReshapeFunc(myReshape);
	glutMainLoop();
}

