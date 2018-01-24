/*float v11(Vec3f p, double teta, double phi) {
	return -1 * (float)sin(toRadians(teta));
}

float v12(Vec3f p, double teta, double phi) {
	return -1 * (float)cos(toRadians(phi)) * (float)cos(toRadians(teta));
}

float v13(Vec3f p, double teta, double phi) {
	return -1 * (float)sin(toRadians(phi))*(float)cos(toRadians(teta));
}

float v21(Vec3f p, double teta, double phi) {
	return (float)cos(toRadians(teta));
}

float v22(Vec3f p, double teta, double phi) {
	return -1 * (float)cos(toRadians(phi))*(float)sin(toRadians(teta));
}

float v23(Vec3f p, double teta, double phi) {
	return -1 * (float)sin(toRadians(phi))*(float)sin(toRadians(teta));
}

float v43() {
	return 200;
}

float v33(Vec3f p, double teta, double phi) {
	return -1 * (float)cos(toRadians(phi));
}

float v32(Vec3f p, double teta, double phi) {
	return (float)sin(toRadians(phi));
}

float rotX(Vec3f p, double teta, double phi) {
	return v11(p, teta, phi)*p.x + v21(p, teta, phi)*p.y;
}

float rotY(Vec3f p, double teta, double phi) {
	return v12(p, teta, phi)*p.x + v22(p, teta, phi)*p.y + v32(p, teta, phi)*p.z;
}

float rotZ(Vec3f p, double teta, double phi) {
	return v13(p, teta, phi)*p.x + v23(p, teta, phi)*p.y + v33(p, teta, phi)*p.z + v43();
}*/