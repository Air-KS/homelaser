/*****
	./src/setup/setup.h
 *****/

#ifndef SETUP_H
#define SETUP_H

#include <painlessMesh.h>

// Déclarations des constantes et variables globales
#define MESH_PREFIX "your_mesh_prefix"
#define MESH_PASSWORD "your_mesh_password"
#define MESH_PORT 5555

extern painlessMesh mesh;
extern Scheduler userScheduler;

void Init_WiFi();
void Init_Mesh();
void receivedCallback(uint32_t from, String &msg);

#endif
