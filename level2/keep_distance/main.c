#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_queue
{
	int		x;
	int		y;
	struct s_queue 	*rear;
	struct s_queue	*front;
}t_queue;

char	***make_arr(char ***places, size_t places_rows, size_t places_cols)
{
	char		***new_arr;
	int			i;
	int			j;
	int			k;
	int			arr_size;

	arr_size = 5;
	new_arr = (char ***)malloc(sizeof(char **) * 6);
	i = -1;
	while (++i < arr_size)
		new_arr[i] = (char **)malloc(sizeof(char *) * 6);
	i = -1;
	while (++i < arr_size)
	{
		j = -1;
		while (++j < arr_size)
			new_arr[i][j] = (char *)malloc(sizeof(char) * 6);
	}
	i = -1;
	while (++i < arr_size)
	{
		j = -1;
		while (++j < places_rows)
		{
			k = -1;
			while (++k < places_cols)
				new_arr[i][j][k] = places[i][j][k];
			new_arr[i][j][k] ='\0';
		}
		new_arr[i][j] = NULL;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	reset(char **arr, int x, int y)
{
	if (arr[x][y] == 'A')
		arr[x][y] = 'P';
	else if (arr[x][y] == 'D')
		arr[x][y] = 'O';
}

void	change_value(char **arr, int x, int y)
{
	if (arr[x][y] == 'P')
		arr[x][y] = 'A';
	else if (arr[x][y] == 'O')
		arr[x][y] = 'D';
}

t_queue	*init_queue(int x, int y)
{
	t_queue *new;

	new = malloc(sizeof(t_queue));
	new->front = NULL;
	new->rear = NULL;
	new->x = x;
	new->y = y;
	return (new);
}

t_queue		*last_queue(t_queue *queue)
{
	while (queue->rear != NULL)
	{
		queue = queue->rear;
	}
	return (queue);
}

int		ququeue_size(t_queue *queue)
{
	int		i;

	i = 0;
	while (queue != NULL)
	{
		queue = queue->rear;
		i++;
	}
	return (i);
}

void	add_queue(t_queue **queue, t_queue *rear)
{
	t_queue *last;

	if (*queue == NULL)
	{
		*queue = rear;
	}
	else
	{
		last = last_queue(*queue);
		last->rear = rear;
	}
}

void	delete_queue(t_queue *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
	queue->x = 0;
	queue->y = 0;
	free(queue);
}

void	popfront(t_queue **queue)
{
	t_queue *first_queue;
	t_queue *second_queue;

	first_queue = *queue;
	second_queue = first_queue->rear;
	*queue = second_queue;
	second_queue->front = NULL;
	delete_queue(first_queue);
}

void	print_map(char **arr)
{
	int i;
	int j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
			printf("%c ",arr[i][j]);
		printf("\n");
	}
}

void	popself(t_queue **queue)
{
	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	(*queue)->x = 0;
	(*queue)->y = 0;
	free(*queue);
	*queue = NULL;
}

int		bfs(char **new_arr, int x, int y, size_t places_rows, size_t places_cols, int *flag, t_queue *queue)
{
	static  int index;
	int		x_arr[4] = {0, 1, 0, -1};
	int		y_arr[4] = {1, 0, -1, 0};
	int		temp_x;
	int		temp_y;
	int		i;
	int		cnt;
	t_queue	*new;

	change_value(new_arr, x, y);
	if (*flag)
		return (1);
	if (ququeue_size(queue) >= 2)
		popfront(&queue);
	else
		popself(&queue);
	i = -1;
	while (++i < 4)
	{
		temp_x = x + x_arr[i];
		temp_y = y + y_arr[i];
		if ((temp_x >= 0 && temp_y >= 0) && (temp_x < places_rows && temp_y < places_cols))
		{
			if (new_arr[temp_x][temp_y] == 'O' || new_arr[temp_x][temp_y] == 'P')
			{
				if (new_arr[temp_x][temp_y] == 'P')
					*flag = 1;
				new = init_queue(temp_x, temp_y);
				add_queue(&queue, new);
			}
		}
	}
	cnt = 0;
	if (queue != NULL)
		cnt += bfs(new_arr, queue->x, queue->y, places_rows, places_cols, flag, queue);
	cnt++;
	return (cnt);
}

void	clearing(char **arr)
{
	int i;
	int j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
			reset(arr, i, j);
	}
}

int		bfs_result(char **new_arr, size_t places_rows, size_t places_cols)
{
	int		i;
	int		j;
	int		flag;
	int		result;
	t_queue 	*queue;
	t_queue		*new;

	i = -1;
	while (++i < places_rows)
	{
		j = -1;
		while (++j < places_cols)
		{
			flag = 0;
			result = 0;
			if (new_arr[i][j] == 'P')
			{
				new = init_queue(i, j);
				queue = new;
				result = bfs(new_arr, i, j, places_rows, places_cols, &flag, queue);
				result -= 1;
				clearing(new_arr);
			}
			if (flag && result <= 2)
				return (0);
		}
	}
	return (1);
}

// places_rows는 2차원 배열 places의 행 길이, places_cols는 2차원 배열 places의 열 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int		*solution(const char ***places, size_t places_rows, size_t places_cols)
{
	size_t 	arr_size;
	char	***new_arr;
	int		i;
	int		j;
    int		*answer;

	arr_size = 5;
	answer = (int *)malloc(sizeof(int) * arr_size);
	new_arr = make_arr((char ***)places, places_rows, places_cols);
	i = 0;
	while (i < arr_size)
	{
		answer[i] = bfs_result(new_arr[i], places_rows, places_cols);
		i++;
	}
	//free_arr(new_arr, places_rows, places_cols);
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    return answer;
} 

const char	***main_temp()
{
	int	i;
	int	j;
	int	places_rows = 5;
	int	places_cols = 5;
	int	arr_size = 5;
	const char ***new_arr;


	new_arr = (const char ***)malloc(sizeof(char **) * arr_size + 1);
	i = -1;
	while (++i < arr_size)
		new_arr[i] = (const char **)malloc(sizeof(char *) * places_rows + 1);
	i = -1;
	while (++i < arr_size)
	{
		j = -1;
		while (++j < arr_size)
			new_arr[i][j] = (const char *)malloc(sizeof(char) * places_cols + 1);
	}
	new_arr[0][0] = "POOOP";
	new_arr[0][1] = "OXXOX";
	new_arr[0][2] = "OPXPX";
	new_arr[0][3] = "OOXOX";
	new_arr[0][4] = "POXXP";
	
	new_arr[1][0] = "POOPX";
	new_arr[1][1] = "OXPXP";
	new_arr[1][2] = "PXXXO";
	new_arr[1][3] = "OXXXO";
	new_arr[1][4] = "OOOPP";

	new_arr[2][0] = "PXOPX";
	new_arr[2][1] = "OXOXP";
	new_arr[2][2] = "OXPOX";
	new_arr[2][3] = "OXXOP";
	new_arr[2][4] = "PXPOX";

	new_arr[3][0] = "OOOXX";
	new_arr[3][1] = "XOOOX";
	new_arr[3][2] = "OOOXX";
	new_arr[3][3] = "OXOOX";
	new_arr[3][4] = "OOOOO";

	new_arr[4][0] = "PXPXP";
	new_arr[4][1] = "XPXPX";
	new_arr[4][2] = "PXPXP";
	new_arr[4][3] = "XPXPX";
	new_arr[4][4] = "PXPXP";
	return (new_arr);
}

int		main(void)
{
	const char ***places;
	int *answer;
	int		i;

	places = main_temp();
	answer = solution(places, 5, 5);

	i = 0;
	while (i < 5)
	{
		printf("%d\n", answer[i]);
		i++;
	}
}
