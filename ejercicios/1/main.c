#include "tarea.h"

int main(void)
{
	struct tarea *t1;
	char info[250];

	t1 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE, "Limpiar");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DES, "Barrer cocina");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, "Miguel");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 0);
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_PRIORIDAD, 0);

	curso_tarea_snprintf(info, sizeof(info), t1);
	printf("los valores de la tarea son: %s\n", info);

	curso_tarea_free(t1);
	return 0;
}
