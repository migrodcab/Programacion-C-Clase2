#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea {
	struct tarea	*tareas[10];
	uint32_t	num_tareas;

	uint32_t	flags;
};

struct gestor_tarea *curso_gestor_alloc(void)
{
	return (struct gestor_tarea *)malloc(sizeof(struct gestor_tarea));
}
void curso_gestor_free(struct gestor_tarea *ges)
{
	int i;
	for (i = 0; i < ges->num_tareas; i++)
		curso_tarea_free(ges->tareas[i]);

	xfree(ges);
}

void curso_gestor_attr_unset_tarea(struct gestor_tarea *ges,
					  uint32_t pos)
{
	if (pos > 0 && pos > ges->num_tareas)
		return;

	ges->num_tareas--;
	curso_tarea_free(ges->tareas[pos]);
}

static void curso_gestor_set_data(struct gestor_tarea *ges,
					 uint16_t attr, const void *data)
{
	if (attr > CURSO_GESTOR_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_ATTR_TAREA:
		if (ges->num_tareas > 10) {
			printf("La lista de tareas esta llena\n");
			break;
		}

		ges->tareas[ges->num_tareas] = (struct tarea *)data;
		ges->num_tareas++;
		break;
	}

	ges->flags |= (1 << attr);
}
void curso_gestor_attr_set_str(struct gestor_tarea *ges, uint16_t attr,
				      const char *data)
{
		curso_gestor_set_data(ges, attr, data);
}
void curso_gestor_attr_set_tarea(struct gestor_tarea *ges,
					uint16_t attr, struct tarea *data)
{
	curso_gestor_set_data(ges, attr, data);
}

const void *curso_gestor_attr_get_data(struct gestor_tarea *ges,
					      uint16_t attr, uint32_t pos)
{
	if (!(ges->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_GESTOR_ATTR_NUM_TAREAS:
		return &ges->num_tareas;
	case CURSO_GESTOR_ATTR_TAREA:
		return ges->tareas[pos];
	}
	return NULL;
}

uint32_t curso_gestor_attr_get_u32(struct gestor_tarea *ges,
					  uint16_t attr)
{
	const void *ret = curso_gestor_attr_get_data(ges, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}
const char *curso_gestor_attr_get_str(struct gestor_tarea *ges,
					     uint16_t attr)
{
	return curso_gestor_attr_get_data(ges, attr, 0);
}
struct tarea *curso_gestor_attr_get_tarea(struct gestor_tarea *ges,
						 uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_attr_get_data(ges, attr, pos);
}

int curso_gestor_snprintf(char *buf, size_t size, struct gestor_tarea *ges)
{
	int i, ret = 0;

	ret += snprintf(buf, size,
			"La lista de tareas tiene %d y son:\n", ges->num_tareas);

	for (i = 0; i < ges->num_tareas; i++) {
		ret += curso_tarea_snprintf(buf + ret, size - ret, ges->tareas[i]);
		//ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
