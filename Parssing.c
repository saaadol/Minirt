#include "Minirt.h"

size_t ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int type_check(char *file)
{
    int len;

    if (!file)
        return (1);
    len = ft_strlen(file) - 1;
    while(len >= 0)
    {
        if (file[len] == '.')
            break;
        len--;
    }
    if(!ft_strncmp(file + len, ".rt", 4))
        return (0);
    return (1);
}

size_t lst_size(t_save *list)
{
    t_save *head;
    size_t size;

    head = list;
    size = 0;
    while(head->line)
    {
        size++;
        head = head->next;
    }
    return (size);
}

char **line_maker(t_save *list)
{
    t_save *head;
    char **lines;
    size_t size;
    size_t i;

    head = list;
    i = 0;
    size = lst_size(list);
    lines = malloc(sizeof(char *) * (size + 1));
    while(head->line)
    {
        lines[i] = ft_strdup(head->line);
        i++;
        head = head->next;
    }
    lines[i] = NULL;
    return(lines);
}

void	clear_list(t_save **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		clear_list(&(*list)->next);
    if ((*list)->line)
	    free((*list)->line);
	free(*list);
	*list = NULL;
}

char    **filling_lines(char *file)
{
    t_save *list;
    t_save *head;
    char *buffer;
    char **file_line;
    int fd;

    fd = open(file, O_RDONLY, 0777);
    list = malloc(sizeof(t_save));
    list->line = NULL;
    head = list;
    while(1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
        {
            head->line = NULL;
            head->next = NULL;
            break;
        }
        head->line = ft_strtrim(buffer, " \r\f\t\v");
        head->next = malloc(sizeof(t_save));
        head = head->next;
        free(buffer);
    }
    close(fd);
    file_line = line_maker(list);
    clear_list(&list);
    return (file_line);
}

size_t  file_size(char **str)
{
    size_t i;
    size_t size;

    i = 0;
    size = 0; 
    while(str[i])
    {
        if (ft_strncmp("\n", str[i], ft_strlen(str[i])))
            size++;
        i++;
    }
    return (size);
}

void    free_double(char **str)
{
    size_t i;

    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
}

char **remove_line_break(char **file_name)
{
    char **str;
    size_t i;
    size_t j;
    size_t size;

    i = 0;
    j = 0;
    size = file_size(file_name);
    str = malloc(sizeof(char *) * (size + 1));
    while(file_name[i])
    {
        if (ft_strncmp("\n", file_name[i], ft_strlen(file_name[i])))
        {
            str[j] = ft_strdup(file_name[i]);
            j++;
        }
        i++;
    }
    str[j] = NULL;
    free_double(file_name);
    return (str);
}

int multi_space(char *line)
{
    size_t i;

    i = 0;
    while(line[i])
    {
        if (line[i] == 32 && line[i + 1] == 32)
            return (1);
        i++;
    }
    return (0);
}

size_t no_multi_space_size(char *line)
{
    size_t i;
    size_t size;

    i = 0;
    size = 0;
    while(line[i])
    {
        if (line[i] == 32 && line[i + 1] == 32)
            size++;
        i++;
    }
    return (i - size);
}

char *new_line(char *line)
{
    char *str;
    size_t size;
    size_t i;
    size_t j;

    size = no_multi_space_size(line);
    i = 0;
    j = 0;
    str = malloc(sizeof(char) * (size + 1));
    while(line[i])
    {
        while (line[i] == 32 && line[i + 1] == 32)
            i++;
        str[j] = line[i];
        j++;
        i++;
    }
    str[j] = '\0';
    free(line);
    return (str);
}

void remove_multiple_space(char **file_line)
{
    size_t i = 0;
    while(file_line[i])
    {
        if (multi_space(file_line[i]))
            file_line[i] = new_line(file_line[i]);
        i++;
    }
}

int splite_size(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

double ft_atof(char *str)
{
    double num;
    int flag;
    int signe;
    int size;
    int i;

    i = 0;
    num = 0;
    size = 0;
    signe = 1;
    flag = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            signe = -1;;
        i++;
    }
    while(str[i])
    {
        if (str[i] == '.' && flag == 0)
            flag = i;
        else if (48 <= str[i] && str[i] <= 57)
            num = (num * 10) + str[i] - 48;
        else if (str[i] != '\n')
            return (10.0f);
        i++;
    }
    if (flag != 0)
        size = (i - 1) - flag;
    while(size)
    {
        num = num / 10;
        size--;
    }
    return (num * signe);
}

int matrix_correct(char *str)
{
    size_t i;
    size_t size;

    i = 0;
    size = 0;
    while(str[i])
    {
        if (str[i] == ',')
            size++;
        i++;
    }
    if (size != 2)
        return (1);
    return(0);
}

int check_rgb(char *str)
{
    size_t i;
    int num;

    i = 0;
    num = 0;
    if (matrix_correct(str))
        return (1);
    while(str[i])
    {
        if (str[i] == ',')
        {
            if (num > 255)
                return (1);
            num = 0;
        }
        else if (48 <= str[i] && str[i] <= 57)
            num = (num * 10) + (str[i] - 48);
        else if (str[i] != 32 && str[i] != 9 && str[i] != 10 && str[i] != 11 && str[i] != 12 && str[i] != 13)
            return (1);
        i++; 
    }
    if (num > 255)
        return (1);
    return (0);
}

int Ambient_lightning_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 3)
        return (free_double(splite), 1);
    if (ft_strncmp(splite[0], "A", 2))
        return(free_double(splite), 1);
    if  (0.0f > ft_atof(splite[1]) || ft_atof(splite[1])  > 1.0f)
        return(free_double(splite), 1);
    if (check_rgb(splite[2]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int check_num(char *str, size_t *i)
{
    int flag = 0;
    if (!str[*i] || str[*i] == ',' || str[*i] == '.')
        return (1);
    if (str[*i] == '-' || str[*i] == '+')
        (*i)++;
    if (!str[*i] || str[*i] == ',' || str[*i] == '.')
        return (1);
    while(str[*i])
    {
        if (str[*i] == ',')
            return ((*i)--, 0);
        else if (str[*i] == '.' && flag == 0)
            flag = 1;
        else if (str[*i] < 48 || str[*i] > 57)
            return (1);
        (*i)++;
    }
    (*i)--;
    return (0);
}

int check_num_beta(char *str, size_t *i)
{
    int flag = 0;
    if (!str[*i] || str[*i] == ',' || str[*i] == '.')
        return (1);
    if (str[*i] == '-' || str[*i] == '+')
        (*i)++;
    if (!str[*i] || str[*i] == ',' || str[*i] == '.')
        return (1);
    while(str[*i])
    {
        if (str[*i] == ',')
            return ((*i)--, 0);
        else if (str[*i] == '.' && flag == 0)
            flag = 1;
        else if (str[*i] < 48 || str[*i] > 57)
            return (1);
        (*i)++;
    }
    (*i)--;
    return (0);
}

int xyz_correct(char *str)
{
    size_t i;

    i = 0;
    if (matrix_correct(str))
        return (1);
    while(str[i])
    {
        if (i == 0 || str[i] == ',')
        {
            if (str[i] == ',')
                i++;
            if (check_num(str, &i))
                return (str[i]);
        }
        i++;
    }
    return (0);
}

int xyz_vectors_correct(char *str)
{
    size_t i;

    i = 0;
    if (matrix_correct(str))
        return (1);
    while(str[i])
    {
        if (i == 0 || str[i] == ',')
        {
            if (str[i] == ',')
                i++;
            if (check_num_beta(str, &i))
                return (1);
        }
        i++;
    }
    return (0);
}

int fov_range(char *str)
{
    size_t i;
    size_t flag;
    double num;

    flag = 0;
    i = 0;
    if (!str[i] || str[i] == '-')
        return (1);
    if (str[i] == '+')
        i++;
    while(str[i])
    {
        if (str[i] == '.' && flag == 0)
            flag = 1;
        else if ((str[i] < 48 || str[i] > 57) && str[i] != '\n')
            return (1);
        i++;
    }
    num = ft_atof(str);
    if (num > 180.0f)
        return (1);
    return (0);
}

int camera_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 4)
        return(free_double(splite), 1);
    if (ft_strncmp(splite[0], "C", 2))
        return(free_double(splite), 1);
    if (xyz_correct(splite[1]))
        return(free_double(splite), 1);
    if (xyz_vectors_correct(splite[2]))
        return(free_double(splite), 1);
    if (fov_range(splite[3]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int brightness_ratio_range(char *str)
{
    size_t i;
    size_t flag;
    double num;

    flag = 0;
    i = 0;
    if (!str[i] || str[i] == '-')
        return (1);
    if (str[i] == '+')
        i++;
    while(str[i])
    {
        if (str[i] == '.' && flag == 0)
            flag = 1;
        else if ((str[i] < 48 || str[i] > 57) && str[i] != '\n')
            return (1);
        i++;
    }
    num = ft_atof(str);
    if (num > 1.0f)
        return (1);
    return (0);    
}

int light_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 4)
        return(free_double(splite), 1);
    if (ft_strncmp(splite[0], "L", 2))
        return(free_double(splite), 1);
    if (xyz_correct(splite[1]))
        return(free_double(splite), 1);
    if (brightness_ratio_range(splite[2]))
        return(free_double(splite), 1);
    if (check_rgb(splite[3]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int sphere_diam_correct(char *str)
{
    size_t i;
    size_t flag;

    flag = 0;
    i = 0;
    if (!str[i] || str[i] == '-')
        return (1);
    if (str[i] == '+')
        i++;
    while(str[i])
    {
        if (str[i] == '.' && flag == 0)
            flag = 1;
        else if ((str[i] < 48 || str[i] > 57) && str[i] != '\n')
            return (1);
        i++;
    }
    return (0);
}

int sphere_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 4)
        return(free_double(splite), 1);
    if (ft_strncmp(splite[0], "sp", 3))
        return(free_double(splite), 1);
    if (xyz_correct(splite[1]))
        return(free_double(splite), 1);
    if (sphere_diam_correct(splite[2]))
        return(free_double(splite), 1);
    if (check_rgb(splite[3]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int plane_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 4)
        return(free_double(splite), 1);
    if (ft_strncmp(splite[0], "pl", 3))
        return(free_double(splite), 1);
    if (xyz_correct(splite[1]))
        return(free_double(splite), 1);
    if (xyz_vectors_correct(splite[2]))
        return(free_double(splite), 1);
    if (check_rgb(splite[3]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int cylinder_protection(char *line)
{
    char **splite;
    size_t i;

    i = 0;
    splite = ft_split(line, ' ');
    if (splite_size(splite) != 6)
        return(free_double(splite), 1);
    if (ft_strncmp(splite[0], "cy", 3))
        return(free_double(splite), 1);
    if (xyz_correct(splite[1]))
        return(free_double(splite), 1);
    if (xyz_vectors_correct(splite[2]))
        return(free_double(splite), 1);
    if (sphere_diam_correct(splite[3]))
        return(free_double(splite), 1);
    if (sphere_diam_correct(splite[4]))
        return(free_double(splite), 1);
    if (check_rgb(splite[5]))
        return(free_double(splite), 1);
    return(free_double(splite), 0);
}

int protections(char **lines)
{
    size_t i;
    int flag_a;
    int flag_c;
    int flag_l;

    i = 0;
    flag_a = 0;
    flag_c = 0;
    flag_l = 0;
    while(lines[i])
    {
        if (lines[i][0] == 'A' && flag_a == 0)
        {
            if (Ambient_lightning_protection(lines[i]))
                return (1);
            flag_a = 1;
        }
        else if (lines[i][0] == 'C' && flag_c == 0)
        {
            if (camera_protection(lines[i]))
                return (2);
            flag_c = 1;
        }
        else if (lines [i][0] == 'L' && flag_l == 0)
        {
            if (light_protection(lines[i]))
                return (3);
            flag_l = 1;
        }
        else if (lines[i][0] == 's' && lines[i][1] == 'p')
        {
            if (sphere_protection(lines[i]))
                return (4);
        }
        else if (lines[i][0] == 'p' && lines[i][1] == 'l')
        {
            if (plane_protection(lines[i]))
                return (5);
        }
        else if (lines[i][0] == 'c' && lines[i][1] == 'y')
        {
            if (cylinder_protection(lines[i]))
                return (6);
        }
        else if (lines[i][0] == 'c' && lines[i][1] == 'n')
        {
                return (0);
        }
        else
            return (7);
        i++;
    }
    return (0);
}

char *searching_for(char **file_line, char *type)
{
    char **buffer;
    size_t i;

    i = 0;
    while(file_line[i])
    {
        buffer = ft_split(file_line[i], ' ');
        if (!ft_strncmp(buffer[0], type, ft_strlen(type)))
            return (free_double(buffer), file_line[i]);
        free_double(buffer);
        i++;
    }
    return (NULL);
}

t_a *filling_a(char *line)
{
    t_a *ambient_lightning;
    char **splite;
    char **matrix;

    if (!line)
        return NULL;
    ambient_lightning = malloc(sizeof(t_a));
    splite = ft_split(line, ' ');
    ambient_lightning->light_ratio = ft_atof(splite[1]);
    matrix = ft_split(splite[2], ',');
    ambient_lightning->R = ft_atof(matrix[0]);
    ambient_lightning->G = ft_atof(matrix[1]);
    ambient_lightning->B = ft_atof(matrix[2]);
    ambient_lightning->color = set_color(ambient_lightning->R, ambient_lightning->G, ambient_lightning->B);
    free_double(splite);
    free_double(matrix);
    return (ambient_lightning);
}

t_c *filling_c(char *line)
{
    t_c *camera;
    char **splite;
    char **matrix;

    if (!line)
        return NULL;
    camera = malloc(sizeof(t_c));
    splite = ft_split(line, ' ');
    matrix = ft_split(splite[1], ',');
    camera->x = ft_atof(matrix[0]);
    camera->y = ft_atof(matrix[1]);
    camera->z = ft_atof(matrix[2]);
    free_double(matrix);
    matrix = ft_split(splite[2], ',');
    camera->x_axis = ft_atof(matrix[0]);
    camera->y_axis = ft_atof(matrix[1]);
    camera->z_axis = ft_atof(matrix[2]);
    free_double(matrix);
    camera->FOV = ft_atof(splite[3]);
    free_double(splite);
    return (camera);
}

//bonus
t_cn *filling_cn(char *line)
{
    t_cn *camera;
    char **splite;
    char **matrix;

    if (!line)
        return NULL;
    camera = malloc(sizeof(t_c));
    splite = ft_split(line, ' ');
    matrix = ft_split(splite[1], ',');
    camera->x = ft_atof(matrix[0]);
    camera->y = ft_atof(matrix[1]);
    camera->z = ft_atof(matrix[2]);
    camera->origin = making_new_vector(camera->x, camera->y, camera->z);
    free_double(matrix);
    matrix = ft_split(splite[2], ',');
    camera->x_axis = ft_atof(matrix[0]);
    camera->y_axis = ft_atof(matrix[1]);
    camera->z_axis = ft_atof(matrix[2]);
    camera->direction = making_new_vector(camera->x_axis, camera->y_axis, camera->z_axis);
    free_double(matrix);
    camera->cone_diam = ft_atof(splite[3]);
    camera->cone_height = ft_atof(splite[4]);
    matrix = ft_split(splite[5], ',');
    camera->R = ft_atof(matrix[0]);
    camera->G = ft_atof(matrix[1]);
    camera->B = ft_atof(matrix[2]);
    free(matrix);
    free_double(splite);
    camera->color = set_color(camera->R, camera->G, camera->B);
    return (camera);
}

t_l *filling_l(char *line)
{
    t_l *light;
    char **splite;
    char **matrix;

    if (!line)
        return NULL;
    light = malloc(sizeof(t_c));
    splite = ft_split(line, ' ');
    matrix = ft_split(splite[1], ',');
    light->x = ft_atof(matrix[0]);
    light->y = ft_atof(matrix[1]);
    light->z = ft_atof(matrix[2]);
    free_double(matrix);
    light->light_ratio = ft_atof(splite[2]);
    matrix = ft_split(splite[3], ',');
    light->R = ft_atof(matrix[0]);
    light->G = ft_atof(matrix[1]);
    light->B = ft_atof(matrix[2]);
    light->color = set_color(light->R, light->G, light->B);
    free_double(matrix);
    free_double(splite);
    return (light);
}

t_cy **filling_cy(char **line, int size, t_obj *data)
{
    t_cy **cylinder;
    int i;
    char **splite;
    char **matrix;

    if (!line)
        return NULL;
    i = 0;
    cylinder = malloc(sizeof(t_cy *) * (size + 1));
    while(i < size)
    {
        cylinder[i] = malloc(sizeof(t_cy));
        splite = ft_split(line[i], ' ');
        matrix = ft_split(splite[1], ',');
        cylinder[i]->x = ft_atof(matrix[0]);
        cylinder[i]->y = ft_atof(matrix[1]);
        cylinder[i]->z = ft_atof(matrix[2]);
        free_double(matrix);
        matrix = ft_split(splite[2], ',');
        cylinder[i]->x_axis = ft_atof(matrix[0]);
        cylinder[i]->y_axis = ft_atof(matrix[1]);
        cylinder[i]->z_axis = ft_atof(matrix[2]);
        free_double(matrix);
        cylinder[i]->cylinder_diam = ft_atof(splite[3]);
        cylinder[i]->cylinder_height = ft_atof(splite[4]);
        matrix = ft_split(splite[5], ',');
        cylinder[i]->R = ft_atof(matrix[0]);
        cylinder[i]->G = ft_atof(matrix[1]);
        cylinder[i]->B = ft_atof(matrix[2]);
        cylinder[i]->color = set_color(cylinder[i]->R, cylinder[i]->G, cylinder[i]->B);
        cylinder[i]->data = data;
        free_double(matrix);
        free_double(splite);
        cylinder[i]->origin = making_new_vector(cylinder[i]->x, cylinder[i]->y, cylinder[i]->z);
        cylinder[i]->direction = making_new_vector(cylinder[i]->x_axis, cylinder[i]->y_axis, cylinder[i]->z_axis);
        i++;
    }
    cylinder[i] = NULL;
    free_double(line);
    return (cylinder);
}

t_pl **filling_pl(char **line, int size, t_obj *data)
{
    t_pl **plane;
    char **splite;
    char **matrix;
    int i;

    i = 0;
    if (!line)
        return NULL;
    plane = malloc(sizeof(t_pl *) * (size + 1));
    while(i < size)
    {
        plane[i] = malloc(sizeof(t_pl));
        splite = ft_split(line[i], ' ');
        matrix = ft_split(splite[1], ',');
        plane[i]->x = ft_atof(matrix[0]);
        plane[i]->y = ft_atof(matrix[1]);
        plane[i]->z = ft_atof(matrix[2]);
        free_double(matrix);
        matrix = ft_split(splite[2], ',');
        plane[i]->x_axis = ft_atof(matrix[0]);
        plane[i]->y_axis = ft_atof(matrix[1]);
        plane[i]->z_axis = ft_atof(matrix[2]);
        free_double(matrix);
        matrix = ft_split(splite[3], ',');
        plane[i]->R = ft_atof(matrix[0]);
        plane[i]->G = ft_atof(matrix[1]);
        plane[i]->B = ft_atof(matrix[2]);
        plane[i]->color = set_color(plane[i]->R, plane[i]->G, plane[i]->B);
        plane[i]->data = data;
        free_double(matrix);
        free_double(splite);
        plane[i]->origin = making_new_vector(plane[i]->x, plane[i]->y, plane[i]->z);
        plane[i]->direction = making_new_vector(plane[i]->x_axis, plane[i]->y_axis, plane[i]->z_axis);
        i++;
    }
    plane[i] = NULL;
    free_double(line);
    return (plane);
}

t_sp **filling_sp(char **line, int size, t_obj *data)
{
    t_sp **sphere;
    char **splite;
    char **matrix;
    int i;

    i = 0;
    if (!line)
        return NULL;
    sphere = malloc(sizeof(t_sp *) * (size + 1));
    while(i < size)
    {
        sphere[i] = malloc(sizeof(t_sp));
        splite = ft_split(line[i], ' ');
        matrix = ft_split(splite[1], ',');
        sphere[i]->x = ft_atof(matrix[0]);
        sphere[i]->y = ft_atof(matrix[1]);
        sphere[i]->z = ft_atof(matrix[2]);
        free_double(matrix);
        sphere[i]->sphere_diam = ft_atof(splite[2]);
        matrix = ft_split(splite[3], ',');
        sphere[i]->R = ft_atof(matrix[0]);
        sphere[i]->G = ft_atof(matrix[1]);
        sphere[i]->B = ft_atof(matrix[2]);
        sphere[i]->color = set_color(sphere[i]->R, sphere[i]->G, sphere[i]->B);
        sphere[i]->data = data;
        free_double(matrix);
        free_double(splite);
        sphere[i]->center = making_new_vector(sphere[i]->x, sphere[i]->y, sphere[i]->z);
        i++;
    }
    sphere[i] = NULL;
    free_double(line);
    return (sphere);
}

int find_twins_elements(char **file_line, char *twin)
{
    int i;
    int size;

    i = 0;
    size = 0;
    while(file_line[i])
    {
        if (!ft_strncmp(file_line[i], twin, ft_strlen(twin)))
            size++;
        i++;
    }
    return(size);
}

char **finding_multiple_element(int *len, char **file_line, char *twin)
{
    char **stockage;
    int size;
    int i;
    int j;

    i = 0;
    j = 0;
    size = find_twins_elements(file_line, twin);
    if (size == 0)
        return (NULL);
    stockage = malloc(sizeof(char *) * (size + 1));
    while(file_line[i])
    {
        if (!ft_strncmp(file_line[i], twin, ft_strlen(twin)))
        {
            stockage[j] = ft_strdup(file_line[i]);
            j++;
        }
        i++;
    }
    stockage[j] = NULL;
    *len = size;
    return (stockage);
}

t_obj *filling_data(char **file_line, t_obj *data)
{
    char **line_stockage;
    int size;
    int i;

    i = 0;
    size = 0;
    data->A = filling_a(searching_for(file_line, "A"));
    data->A->data = data;
    data->C = filling_c(searching_for(file_line, "C"));
    data->C->data = data;
    data->L = filling_l(searching_for(file_line, "L"));
    data->L->data = data;
    data->cn = filling_cn(searching_for(file_line, "cn"));
    data->cn->data = data;

    line_stockage = finding_multiple_element(&size, file_line, "cy");
    data->cy = filling_cy(line_stockage, size, data);
    line_stockage = finding_multiple_element(&size, file_line, "pl");
    data->pl = filling_pl(line_stockage, size, data);
    line_stockage = finding_multiple_element(&size, file_line, "sp");
    data->sp = filling_sp(line_stockage, size, data);
    return (data);
}

int    parssing(char *file, t_obj *data)
{
    char **file_line;
    char **stock;

    if (type_check(file))
        return (1);
    stock = filling_lines(file);
    file_line = remove_line_break(stock);
    remove_multiple_space(file_line);
    if(protections(file_line))
        return (free_double(file_line), 1);
    data = filling_data(file_line, data);
    return (free_double(file_line), 0);
}