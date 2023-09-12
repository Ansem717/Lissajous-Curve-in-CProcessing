//---------------------------------------------------------
// file:	main.c
// author:	Andy Malik
// email:	andy.malik@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define VERTEX_COUNT 360

double angle_h = 0;
double angle_v = 0;
double x_speed = 0.02;
double y_speed = 0.02;
float hx = 0;
float hy = 0;
float vx = 0;
float vy = 0;

//Array of vertexes
float curve_verticies_x[VERTEX_COUNT];
float curve_verticies_y[VERTEX_COUNT];

int curve_vertex_tracker = 0;


void game_init(void)
{
	CP_System_SetWindowSize(400, 400);
	CP_System_SetFrameRate(60);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(155, 155, 155, 255));
	CP_Settings_StrokeWeight(3.0);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(250, 75, 100);
	CP_Graphics_DrawCircle(75, 250, 100);

	hx = 50 * (float)cos(angle_h);
	hy = 50 * (float)sin(angle_h);
	vx = 50 * (float)cos(angle_v);
	vy = 50 * (float)sin(angle_v);

	CP_Settings_Fill(CP_Color_Create(100, 200, 255, 255));
	CP_Settings_StrokeWeight(1.5);
	CP_Graphics_DrawCircle(hx + 250, hy + 75, 15);
	CP_Graphics_DrawCircle(vx + 75, vy + 250, 15);

	angle_h += x_speed;
	angle_v += y_speed;

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

	int len = snprintf(NULL, 0, "%.2f", x_speed);
	char* result = malloc(len + 1);
	snprintf(result, len + 1, "%.0f", x_speed * 50);
	CP_Font_DrawText(result, 247, 80);
	free(result);

	result = malloc(len + 1);
	snprintf(result, len + 1, "%.0f", y_speed * 50);
	CP_Font_DrawText(result, 72, 255);
	free(result);

	CP_Settings_StrokeWeight(0.75);
	CP_Graphics_DrawLine(hx + 250, hy + 75, hx + 250, 400);
	CP_Graphics_DrawLine(vx + 75, vy + 250, 400, vy + 250);
	
	CP_Settings_NoFill();
	CP_Settings_StrokeWeight(1);
	CP_Graphics_BeginShape();

	if (curve_vertex_tracker == VERTEX_COUNT) {
		curve_vertex_tracker = 0;
	}

	curve_verticies_x[curve_vertex_tracker] = hx + 250;
	curve_verticies_y[curve_vertex_tracker] = vy + 250;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		if (curve_verticies_x[i] > 0) {
			CP_Graphics_AddVertex(curve_verticies_x[i], curve_verticies_y[i]);
		}
		//CP_Graphics_DrawPoint(curve_verticies_x[i], curve_verticies_y[i]);
	}
	//CP_Graphics_AddVertex(curve_verticies_x[0], curve_verticies_y[0]);

	curve_vertex_tracker += 1;

	CP_Graphics_EndShape();


	if (CP_Input_KeyReleased(KEY_LEFT) || CP_Input_KeyReleased(KEY_A)) {
		 x_speed -= 0.02;
		if (x_speed <= 0.02) x_speed = 0.02;
		angle_h = 0;
		angle_v = 0;
	}

	if (CP_Input_KeyReleased(KEY_RIGHT) || CP_Input_KeyReleased(KEY_D)) {
		 x_speed += 0.02;
		if (x_speed >= 0.26) x_speed = 0.26;
		angle_h = 0;
		angle_v = 0;
	}

	if (CP_Input_KeyReleased(KEY_DOWN) || CP_Input_KeyReleased(KEY_S)) {
		y_speed -= 0.02;
		if (y_speed <= 0.02) y_speed = 0.02;
		angle_h = 0;
		angle_v = 0;
	}

	if (CP_Input_KeyReleased(KEY_UP) || CP_Input_KeyReleased(KEY_W)) {
		 y_speed += 0.02;
		if (y_speed >= 0.26) y_speed = 0.26;
		angle_h = 0;
		angle_v = 0;
	}

}

void game_exit(void)
{
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
