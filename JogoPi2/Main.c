#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define LARGURA 640
#define ALTURA 480
#define FPS 60.0
#define FrameFps 25.0
#define InimigoFps 11.0
#define Chao 420

//struct de objeto
struct objeto
{
	ALLEGRO_BITMAP* imagem;
	float x;
	float y;
	int largura;
	int altura;
	int vida;
};

//                  
typedef struct objeto Objeto;

Objeto* personagem, * sprite_parado, * goblin, * goblin2, * espada, * processador, * processador_mini, * placa_mae, * placa_mae_mini, * sprite_atacando, * inventario;//ponteiros de objeto
Objeto* placa_de_video, * placa_de_video_mini, * memoria_ram, * memoria_ram_mini, * portal, * inimigo1_mapa2, * inimigo2_mapa2, * boss, * boss_sword;//ponteiros de objeto
Objeto* chave;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_TIMER* frametimer = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_SAMPLE* musica = NULL;
ALLEGRO_SAMPLE_INSTANCE* songInstance = NULL;
ALLEGRO_SAMPLE* clique_menu = NULL;
ALLEGRO_SAMPLE* som_espada = NULL;
ALLEGRO_SAMPLE* pegar_item = NULL;

//ponteiros de bitmap
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* background2 = NULL;
ALLEGRO_BITMAP* background_jogo1 = NULL;
ALLEGRO_BITMAP* chao = NULL;
ALLEGRO_BITMAP* chao_fim = NULL;
ALLEGRO_BITMAP* atributos = NULL;
ALLEGRO_BITMAP* img0 = NULL;
ALLEGRO_BITMAP* img1 = NULL;
ALLEGRO_BITMAP* img2 = NULL;
ALLEGRO_BITMAP* img3 = NULL;
ALLEGRO_BITMAP* img4 = NULL;
ALLEGRO_BITMAP* img5 = NULL;
ALLEGRO_BITMAP* img6 = NULL;
ALLEGRO_BITMAP* img7 = NULL;
ALLEGRO_BITMAP* img8 = NULL;
ALLEGRO_BITMAP* img9 = NULL;
ALLEGRO_BITMAP* img10 = NULL;
ALLEGRO_BITMAP* background33 = NULL;
ALLEGRO_BITMAP* inventario_memoria_ram = NULL;
ALLEGRO_BITMAP* plataforma1 = NULL;
ALLEGRO_BITMAP* plataforma2 = NULL;
ALLEGRO_BITMAP* plataforma3 = NULL;
ALLEGRO_BITMAP* chao2 = NULL;
ALLEGRO_BITMAP* chao2_fim = NULL;
ALLEGRO_BITMAP* inventario_chave = NULL;
ALLEGRO_BITMAP* chao3 = NULL;
ALLEGRO_BITMAP* chao3_fim = NULL;
ALLEGRO_BITMAP* background3 = NULL;
ALLEGRO_BITMAP* pilar1 = NULL;
ALLEGRO_BITMAP* caixa = NULL;
ALLEGRO_BITMAP* plataforma_pedra = NULL;
ALLEGRO_BITMAP* morreu1 = NULL;
ALLEGRO_BITMAP* venceu1 = NULL;
ALLEGRO_BITMAP* infoss = NULL;
ALLEGRO_BITMAP* creditoss = NULL;
ALLEGRO_BITMAP* controless = NULL;
ALLEGRO_BITMAP* frame = NULL;
ALLEGRO_BITMAP* frame2 = NULL;
ALLEGRO_BITMAP* placa_mae_inv = NULL;
ALLEGRO_BITMAP* processador_inv = NULL;
ALLEGRO_BITMAP* inventario_processador = NULL;
ALLEGRO_BITMAP* inventario_placa_mae = NULL;
ALLEGRO_BITMAP* inventario_placa_de_video = NULL;
ALLEGRO_BITMAP* desc_placa_mae = NULL;
ALLEGRO_BITMAP* desc_processador = NULL;
ALLEGRO_BITMAP* desc_placa_de_video = NULL;
ALLEGRO_BITMAP* desc_memoria_ram = NULL;





//variaveis globais
int pressionadox = 0;
int i = 0;
int aux = 0;
int contador_aux = 0;
int j = 0;
int k = 0;
int l = 0;
int lado;
int lado_inimigo1;
int lado_inimigo2;
int yInicial1 = 0;
int yInicial2 = 0;
//bolleanos de objetos
bool draw = false, draw2 = true, ativo = false, item_processador = false, item_processador_mini = false, item_placa = false, item_placa_mini = false;
bool item_placa_de_video = false, item_placa_de_video_mini = false, item_memoria_ram = false, item_memoria_ram_mini = false;
bool descricao_processador, descricao_placa_mae, descricao_placa_de_video, descricao_memoria_ram;
bool item_chave_mini = false;
bool item_chave = false, pegou_chave = false;

//teste
bool inv_placa = false;
bool inv_processador = false;
bool inventarioo = false;
bool portal_ativo = false;


//variaveis do mapa

int colunas_mapa1 = 11;
int linhas_mapa1 = 9;
int tileSize = 59;
int mapa_atual = 1;



//matrizes�para um tile maps
//pedra (chao) = 20
//caixa = 40
//pilar1 = 50
//plataforma pedra = 60
int map1[9][11] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 7, 8, 9, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 7, 8, 8, 9, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
				  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3} };

int map2[9][11] = { {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 60, 60, 60, 60, 60, 60, 60, 60, 60, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {60, 60, 60, 0, 0, 60, 60, 0, 0, 60, 60},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
				  {21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21} };

int map3[9][11] = { {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 10, 0, 0, 0, 10, 0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
				  {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11} };


int pressionando = 0;
float velocidade_movimento = 4.5;
float velx;
float vely;
float pLimite;

velx = 0;
vely = 0;

atacando = false, espada_ativa = false;
float velocidade_pulo = 13;
int caindo = 1;
int pulando = 0;

const float gravidade = 0.80;

int sourceX = 0, sourceX_inimigo = 0, sourceX_atacando;

bool inimigo1 = true, inimigo2 = true, inimigo3 = true, inimigo4 = true;
float velocidade_inimigo = 1.5;

bool chefao = false, chefao_ataque = false, chefao_espada = false;

float velocidade_projetil = 10.0, projetil_chefao = 8.0;
int posicao_projetil = 0;

ALLEGRO_KEYBOARD_STATE key_state;

// Funcao que inicializa as coisas
void inicializa��o() {

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_primitives_addon();

	//audio
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);

	timer = al_create_timer(1.0 / FPS);
	frametimer = al_create_timer(1.0 / FrameFps);

	janela = al_create_display(LARGURA, ALTURA);

	fila_eventos = al_create_event_queue();

	al_set_window_title(janela, "Em busca do Hardware Perdido");

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_timer_event_source(frametimer));

}

// a personagem
// b obj
// aw = largura
// Ele pega a posicao do personagem e compara com o inico e fim do objeto x, e compara o y tambem
int colisao(float ax, float ay, float bx, float by, int aw, int ah, int bw, int bh, int limite) {
	if (ax + aw > bx && ax < bx + limite + bw && ay + ah > by && ay < by + bh) {
		return 1;
	}
	else {
		return 0;
	}
}


// Fun��o movimenta��o
void movimentacao(ALLEGRO_EVENT evento) {


	if (evento.timer.source == timer) {

		ativo = true;

		pressionando = 0;

		if (al_key_down(&key_state, ALLEGRO_KEY_UP) && pulando == 0 && caindo == 0) {
			pulando = 1;

			pLimite = personagem->y;

		}
		if (al_key_down(&key_state, ALLEGRO_KEY_Z) && !atacando && !espada_ativa) {
			atacando = true;
			if (!espada_ativa) {
				al_play_sample(som_espada, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				espada->y = personagem->y;
				l = j;
			}

			espada_ativa = true;
		}
		else if (al_key_down(&key_state, ALLEGRO_KEY_E)) {
			inventarioo = true;
		}
		else if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)) {
			inventarioo = false;
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
			velx = velocidade_movimento;

			j = 1;

			pressionando = 1;
		}
		else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
			velx = -velocidade_movimento;

			j = 0;

			pressionando = 1;
		}
		else {
			ativo = false;
			velx = 0;
		}

		if (pulando == 1 && personagem->y > pLimite - 25) {
			//pulando = 0;
			personagem->y += vely;
			vely = -velocidade_pulo;
			caindo = 1;
		}
		else if (caindo == 1) {
			pulando = 0;
			vely += gravidade;
			personagem->y += vely;
		}
		else {
			vely = 0;
		}

		/*if (!pulando) {
			vely += gravidade;
		}
		else {
			vely = 0;
		}*/
		if (personagem->x >= -1 && personagem->x + personagem->largura / 10 <= 639) {
			personagem->x += velx;
		}
		if (personagem->x <= -1) {
			personagem->x = 0;
		}
		else if (personagem->x + personagem->largura / 10 >= 639) {
			personagem->x = 638 - personagem->largura / 10;
		}


		/*if (pulando) {
			personagem->y = Chao - 49;
		}*/
		//movimentacao dos inimigos do maoa 1
		if (inimigo1 && personagem->x - goblin->x < 0) {
			goblin->x -= velocidade_inimigo;
			k = 0;
		}
		else if (inimigo1 && personagem->x - goblin->x > 0) {
			goblin->x += velocidade_inimigo;
			k = 1;
		}

		if (inimigo2 && lado == 0) {
			goblin2->x -= velocidade_inimigo;
			if (goblin2->x <= tileSize * 4 + 5) {
				lado = 1;
			}
		}
		if (inimigo2 && lado == 1) {
			goblin2->x += velocidade_inimigo;
			if (goblin2->x >= tileSize * 4 + tileSize * 4 - 50) {
				lado = 0;
			}
		}

		if (espada_ativa && l == 1) {
			espada->x += velocidade_projetil;
		}
		else if (espada_ativa && l == 0) {
			espada->x -= velocidade_projetil;
		}
		else {
			espada->x = personagem->x;
		}
		//movimenta��o dos inimigos mapa 2
		if (mapa_atual == 2) {
			if (inimigo3 && personagem->x - inimigo1_mapa2->x < 0) {
				inimigo1_mapa2->x -= velocidade_inimigo;
				lado_inimigo1 = 0;
			}
			else if (inimigo3 && personagem->x - inimigo1_mapa2->x > 0) {
				inimigo1_mapa2->x += velocidade_inimigo;
				lado_inimigo1 = 1;
			}

			if (inimigo4 && lado_inimigo2 == 0) {
				inimigo2_mapa2->x -= velocidade_inimigo;
				if (inimigo2_mapa2->x <= tileSize * 1 + 5) {
					lado_inimigo2 = 1;
				}
			}
			if (inimigo4 && lado_inimigo2 == 1) {
				inimigo2_mapa2->x += velocidade_inimigo;
				if (inimigo2_mapa2->x >= tileSize * 1 + tileSize * 9 - 50) {
					lado_inimigo2 = 0;
				}
			}
		}
		//Fase do boss (ataque e vida)
		if (mapa_atual == 3) {
			if (chefao && boss->vida < 20 && boss->vida > 0) {
				chefao_ataque = true;
			}
			if (chefao_ataque && !chefao_espada) {
				boss_sword->y = personagem->y;
				chefao_espada = true;
			}
			if (chefao_espada) {
				boss_sword->x -= projetil_chefao;
			}
			else {
				boss_sword->x = boss->x + 50;

			}
		}
	}

	//controle de sprites
	if (evento.timer.source == frametimer) {

		if (ativo) {
			sourceX += al_get_bitmap_width(personagem->imagem) / 10;
		}
		else {
			sourceX = 1;
		}
		if (sourceX >= al_get_bitmap_width(personagem->imagem)) {
			sourceX = 1;
		}

		if (pressionando == 1) {
			draw = true;
		}

		if (pressionando == 0) {

			i++;

			if (i > 10) {
				i = 0;
			}

			draw2 = true;
		}

		if (atacando) {
			sourceX_atacando += al_get_bitmap_width(sprite_atacando->imagem) / 10;
		}
		else {
			sourceX_atacando = 0;
		}
		if (sourceX_atacando >= al_get_bitmap_width(sprite_atacando->imagem)) {
			sourceX_atacando = 0;
			atacando = false;
		}
	}

	//if (evento.timer.source == inimigotimer) {

	if (inimigo1) {
		sourceX_inimigo = al_get_bitmap_width(goblin->imagem) / 4;
	}
	else {
		sourceX_inimigo = 0;
	}
	if (sourceX_inimigo >= al_get_bitmap_width(goblin->imagem)) {
		sourceX_inimigo = 0;
	}
	//}


}
//funcao desenha void para desenhar sprites e imagens que aparecem no decorrer do jogo
void desenha(ALLEGRO_EVENT evento) {


	if (atacando) {
		al_draw_bitmap_region(sprite_atacando->imagem, sourceX_atacando, 0, sprite_atacando->largura / 10, sprite_atacando->altura, personagem->x - 3, personagem->y - 11, j);

	}
	else {
		if (draw) {
			draw = false;
			//frame = al_create_sub_bitmap(personagem->imagem, (personagem->largura / 10) * i, 0, personagem->largura / 10 - 5, personagem->altura);
			al_draw_bitmap_region(personagem->imagem, sourceX, 0, personagem->largura / 10, personagem->altura, personagem->x, personagem->y, j);
		}

		else if (draw2) {
			draw2 = false;
			frame2 = al_create_sub_bitmap(sprite_parado->imagem, (sprite_parado->largura / 11) * i, 0, sprite_parado->largura / 11, sprite_parado->altura);
			al_draw_bitmap(frame2, personagem->x, personagem->y, j);
			al_flip_display();

		}
	}


	if (inimigo1) {
		al_draw_bitmap_region(goblin->imagem, sourceX_inimigo, 0, goblin->largura / 4, goblin->altura, goblin->x, goblin->y, k);
	}
	if (inimigo2) {
		al_draw_bitmap_region(goblin2->imagem, sourceX_inimigo, 0, goblin2->largura / 4, goblin2->altura, goblin2->x, goblin2->y, lado);
	}
	if (mapa_atual == 2) {
		if (inimigo3) {
			al_draw_bitmap(inimigo1_mapa2->imagem, inimigo1_mapa2->x, inimigo1_mapa2->y, lado_inimigo1);
		}
		if (inimigo4) {
			al_draw_bitmap(inimigo2_mapa2->imagem, inimigo2_mapa2->x, inimigo2_mapa2->y, lado_inimigo2);
		}
	}
	if (mapa_atual == 3) {
		if (chefao) {
			al_draw_bitmap(boss->imagem, boss->x, boss->y, 1);
			al_draw_rectangle(boss->x + 45, boss->y - 5, boss->x + 45 + boss->vida * 5, boss->y + 3, al_map_rgb(255, 0, 0), 10);
		}
		if (chefao_espada) {
			al_draw_bitmap(boss_sword->imagem, boss_sword->x, boss_sword->y, 1);
		}
	}
	if (espada_ativa) {
		al_draw_bitmap(espada->imagem, espada->x, espada->y, l);
	}
	if (item_processador) {
		al_draw_bitmap(processador->imagem, processador->x, processador->y, 0);
	}
	if (item_processador_mini) {
		al_draw_bitmap(processador_mini->imagem, processador_mini->x, processador_mini->y, 0);
		inventario->imagem = inventario_processador;

	}
	if (item_placa) {
		al_draw_bitmap(placa_mae->imagem, placa_mae->x, placa_mae->y, 0);
	}
	if (item_placa_mini) {
		al_draw_bitmap(placa_mae_mini->imagem, placa_mae_mini->x, placa_mae_mini->y, 0);
		inventario->imagem = inventario_placa_mae;
	}

	if (item_memoria_ram) {
		al_draw_bitmap(memoria_ram->imagem, memoria_ram->x, memoria_ram->y, 0);
	}
	if (item_memoria_ram_mini) {
		al_draw_bitmap(memoria_ram_mini->imagem, memoria_ram_mini->x, memoria_ram_mini->y, 0);
		inventario->imagem = inventario_memoria_ram;
	}
	if (item_placa_de_video) {
		al_draw_bitmap(placa_de_video->imagem, placa_de_video->x, placa_de_video->y, 0);
	}
	if (item_placa_de_video_mini) {
		al_draw_bitmap(placa_de_video_mini->imagem, placa_de_video_mini->x, placa_de_video_mini->y, 0);
		inventario->imagem = inventario_placa_de_video;
	}

	if (inv_placa)
		al_draw_bitmap(placa_mae_inv, 0, 0, 0);
	//aqui!!
	if (inventarioo)
		al_draw_bitmap(inventario->imagem, 0, 0, 0);
	if (descricao_processador) {
		al_draw_bitmap(desc_processador, 0, 0, 0);
	}
	if (descricao_placa_mae) {
		al_draw_bitmap(desc_placa_mae, 0, 0, 0);
	}
	if (descricao_placa_de_video) {
		al_draw_bitmap(desc_placa_de_video, 0, 0, 0);
	}
	if (descricao_memoria_ram) {
		al_draw_bitmap(desc_memoria_ram, 0, 0, 0);
	}
	if (portal_ativo && !inventarioo) {
		al_draw_bitmap(portal->imagem, portal->x, 150, 0);
	}
	if (item_chave) {
		al_draw_bitmap(chave->imagem, chave->x, chave->y, 0);
	}
	/*colocar a intro aqui?*/


}

//funcao void que desenha de acordo com a matriz de tilemap as sprites que correspondem a cada mapa
void desenhar_mapa(int mapa[9][11]) {

	int cont_i, cont_j;

	for (cont_i = 0; cont_i < linhas_mapa1; cont_i++) {
		for (cont_j = 0; cont_j < colunas_mapa1; cont_j++) {
			if (mapa[cont_i][cont_j] == 0) {

			}
			else if (mapa[cont_i][cont_j] == 2) {
				al_draw_bitmap_region(chao, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 3) {
				al_draw_bitmap_region(chao_fim, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 7) {
				al_draw_bitmap_region(plataforma1, tileSize * 0, tileSize * 0, tileSize, 44, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 8) {
				al_draw_bitmap_region(plataforma2, tileSize * 0, tileSize * 0, tileSize, 44, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 9) {
				al_draw_bitmap_region(plataforma3, tileSize * 0, tileSize * 0, tileSize, 44, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 20) {
				al_draw_bitmap_region(chao2, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 21) {
				al_draw_bitmap_region(chao2_fim, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 60) {
				al_draw_bitmap_region(plataforma_pedra, tileSize * 0, tileSize * 0, tileSize, 44, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 10) {
				al_draw_bitmap_region(chao3, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
			else if (mapa[cont_i][cont_j] == 11) {
				al_draw_bitmap_region(chao3_fim, tileSize * 0, tileSize * 0, tileSize, tileSize, cont_j * tileSize, cont_i * tileSize, 0);
			}
		}
	}
}

// Main
int main(void) {

	inicializa��o();
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();

	// Carrega as imagens usadas durante o jogo
	background = al_load_bitmap("imagens/menu2.jpg");
	atributos = al_load_bitmap("imagens/atributos.png");
	background_jogo1 = al_load_bitmap("imagens/background.jpg");
	background2 = al_load_bitmap("sprites/background2.jpg");
	chao = al_load_bitmap("sprites/chao.jpg");
	chao_fim = al_load_bitmap("sprites/chao_fim.jpg");
	plataforma1 = al_load_bitmap("sprites/plataforma1.png");
	plataforma2 = al_load_bitmap("sprites/plataforma2.png");
	plataforma3 = al_load_bitmap("sprites/plataforma3.png");
	chao2 = al_load_bitmap("sprites/plataforma4.png");
	chao2_fim = al_load_bitmap("sprites/plataforma5.png");
	pilar1 = al_load_bitmap("sprites/pilar1.png");
	caixa = al_load_bitmap("sprites/caixa.png");
	plataforma_pedra = al_load_bitmap("sprites/plataforma_pedra.png");
	controless = al_load_bitmap("imagens/controles.png");


	morreu1 = al_load_bitmap("imagens/morreu.png");
	venceu1 = al_load_bitmap("imagens/venceu.png");

	img0 = al_load_bitmap("imagens/img0.jpg");
	img1 = al_load_bitmap("imagens/img1.jpg");
	img2 = al_load_bitmap("imagens/img2.jpg");
	img3 = al_load_bitmap("imagens/img3.jpg");
	img4 = al_load_bitmap("imagens/img4.jpg");
	img5 = al_load_bitmap("imagens/img5.jpg");
	img6 = al_load_bitmap("imagens/img6.jpg");
	img7 = al_load_bitmap("imagens/img7.jpg");
	img8 = al_load_bitmap("imagens/nomeJogo.jpg");
	img9 = al_load_bitmap("imagens/nomesIntegrantes.jpg");
	img10 = al_load_bitmap("imagens/transicao.jpg");

	inventario_chave = al_load_bitmap("imagens/inventario_chave.png");

	chao3 = al_load_bitmap("Sprites/chao3.png");
	chao3_fim = al_load_bitmap("Sprites/chao3_fim.png");


	infoss = al_load_bitmap("imagens/infos.jpg");
	creditoss = al_load_bitmap("imagens/creditos.jpg");
	inventario_placa_de_video = al_load_bitmap("imagens/inventario_placa_de_video.png");
	// teste
	processador_inv = al_load_bitmap("imagens/pc.png");
	placa_mae_inv = al_load_bitmap("imagens/pcmae.png");
	inventario = al_load_bitmap("imagens/inventario.png");
	inventario_processador = al_load_bitmap("imagens/inventario_processador.png");
	inventario_placa_mae = al_load_bitmap("imagens/inventario_placa_mae.png");
	inventario_memoria_ram = al_load_bitmap("imagens/inventario_memoria_ram.png");
	musica = al_load_sample("musica.ogg");
	fonte = al_load_font("Fontes/arial.ttf", 48, 0);

	pegar_item = al_load_sample("pegar_item.wav");
	clique_menu = al_load_sample("clique_menu.wav");//Som de clique
	som_espada = al_load_sample("som_espada.wav");
	background3 = al_load_bitmap("imagens/background3.jpg");
	background33 = al_load_bitmap("imagens/portal3.png");

	desc_processador = al_load_bitmap("imagens/desc_processador.png");
	desc_placa_mae = al_load_bitmap("imagens/desc_placa_mae.png");
	desc_memoria_ram = al_load_bitmap("imagens/desc_memoria_ram.png");
	desc_placa_de_video = al_load_bitmap("imagens/desc_placa_de_video.png");


	songInstance = al_create_sample_instance(musica);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	//Carregando sons
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);//Reservando canais de audio no mixer principal

	//cria os objetos usando a struct objeto
	personagem = (Objeto*)malloc(sizeof(Objeto));
	personagem->imagem = al_load_bitmap("Sprites/MC_Sprite_walk.png");
	personagem->largura = 500;
	personagem->altura = 49;
	personagem->y = 0;
	personagem->x = 20;
	personagem->vida = 3;

	sprite_parado = (Objeto*)malloc(sizeof(Objeto));
	sprite_parado->imagem = al_load_bitmap("Sprites/MC_Sprite_idle.png");
	sprite_parado->x = personagem->x;
	sprite_parado->largura = 440;
	sprite_parado->altura = 49;
	sprite_parado->y = personagem->y;

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	goblin = (Objeto*)malloc(sizeof(Objeto));
	goblin->imagem = al_load_bitmap("Sprites/goblins.png");
	goblin->x = 300;
	goblin->altura = 49;
	goblin->y = Chao - goblin->altura;
	goblin->largura = 246;
	goblin->vida = 6;

	goblin2 = (Objeto*)malloc(sizeof(Objeto));
	goblin2->imagem = al_load_bitmap("Sprites/goblins.png");
	goblin2->x = tileSize * 5;
	goblin2->altura = 49;
	goblin2->y = tileSize * 5 - goblin2->altura;
	goblin2->largura = 246;
	goblin2->vida = 5;

	inimigo1_mapa2 = (Objeto*)malloc(sizeof(Objeto));
	inimigo1_mapa2->imagem = al_load_bitmap("Sprites/inimigo2.png");
	inimigo1_mapa2->x = tileSize * 5;
	inimigo1_mapa2->altura = 90;
	inimigo1_mapa2->y = Chao - inimigo1_mapa2->altura;
	inimigo1_mapa2->largura = 41;
	inimigo1_mapa2->vida = 4;

	inimigo2_mapa2 = (Objeto*)malloc(sizeof(Objeto));
	inimigo2_mapa2->imagem = al_load_bitmap("Sprites/inimigo2.png");
	inimigo2_mapa2->x = tileSize * 7;
	inimigo2_mapa2->altura = 90;
	inimigo2_mapa2->y = tileSize * 3 - inimigo1_mapa2->altura;
	inimigo2_mapa2->largura = 41;
	inimigo2_mapa2->vida = 4;

	chave = (Objeto*)malloc(sizeof(Objeto));
	chave->imagem = al_load_bitmap("Sprites/chave.png");
	chave->altura = 50;
	chave->largura = 30;
	chave->x = 700;
	chave->y = Chao - chave->altura;


	boss = (Objeto*)malloc(sizeof(Objeto));
	boss->imagem = al_load_bitmap("Sprites/boss.png");
	boss->x = 450;
	boss->altura = 350;
	boss->y = Chao - boss->altura;
	boss->largura = 192;
	boss->vida = 20;

	boss_sword = (Objeto*)malloc(sizeof(Objeto));
	boss_sword->imagem = al_load_bitmap("Sprites/boss_sword.png");
	boss_sword->x = boss->x + 50;
	boss_sword->altura = 41;
	boss_sword->y = 0;
	boss_sword->largura = 115;

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sprite_atacando = (Objeto*)malloc(sizeof(Objeto));
	sprite_atacando->imagem = al_load_bitmap("Sprites/MC_Sprite_attack.png");
	sprite_atacando->largura = 649;
	sprite_atacando->altura = 61;
	sprite_atacando->y = personagem->y;
	sprite_atacando->x = personagem->x;

	espada = (Objeto*)malloc(sizeof(Objeto));
	espada->imagem = al_load_bitmap("Sprites/sword.png");
	espada->largura = 65;
	espada->altura = 16;
	espada->y = personagem->y + 30;
	espada->x = personagem->x + 10;

	//Criando objeto do item
	processador = (Objeto*)malloc(sizeof(Objeto));
	processador->imagem = al_load_bitmap("imagens/processador.jpg");
	processador->largura = 63;
	processador->altura = 57;
	processador->x = 700;
	processador->y = Chao - processador->altura;

	processador_mini = (Objeto*)malloc(sizeof(Objeto));
	processador_mini->imagem = al_load_bitmap("imagens/processador_mini.jpg");
	processador_mini->largura = 36;
	processador_mini->altura = 33;
	processador_mini->x = 50;
	processador_mini->y = 100;

	// Placa Mae
	placa_mae = (Objeto*)malloc(sizeof(Objeto));
	placa_mae->imagem = al_load_bitmap("imagens/placamae.jpg");
	placa_mae->largura = 63;
	placa_mae->altura = 57;
	placa_mae->x = 500;
	placa_mae->y = Chao - placa_mae->altura;

	// Placa Mae Mini
	placa_mae_mini = (Objeto*)malloc(sizeof(Objeto));
	placa_mae_mini->imagem = al_load_bitmap("imagens/placamaemini.jpg");
	placa_mae_mini->largura = 36;
	placa_mae_mini->altura = 33;
	placa_mae_mini->x = 10;
	placa_mae_mini->y = 100;

	// Inventario
	inventario = (Objeto*)malloc(sizeof(Objeto));
	inventario->imagem = al_load_bitmap("imagens/inventario.png");
	inventario->largura = 640;
	inventario->altura = 480;


	portal = (Objeto*)malloc(sizeof(Objeto));
	portal->imagem = al_load_bitmap("Sprites/portal.png");
	portal->largura = 57;
	portal->altura = 124;
	portal->x = 570;
	portal->y = 260;


	// Placa de video
	placa_de_video = (Objeto*)malloc(sizeof(Objeto));
	placa_de_video->imagem = al_load_bitmap("imagens/placa_de_video.png");
	placa_de_video->largura = 63;
	placa_de_video->altura = 57;
	placa_de_video->x = 300;
	placa_de_video->y = Chao - placa_de_video->altura;
	// Placa de video mini
	placa_de_video_mini = (Objeto*)malloc(sizeof(Objeto));
	placa_de_video_mini->imagem = al_load_bitmap("imagens/placa_de_video_mini.png");
	placa_de_video_mini->largura = 36;
	placa_de_video_mini->altura = 33;
	placa_de_video_mini->x = 130;
	placa_de_video_mini->y = 100;
	// Memoria ram
	memoria_ram = (Objeto*)malloc(sizeof(Objeto));
	memoria_ram->imagem = al_load_bitmap("imagens/memoria_ram.png");
	memoria_ram->largura = 95;
	memoria_ram->altura = 43;
	memoria_ram->x = 300;
	memoria_ram->y = 100;
	// Memoria ram MINI
	memoria_ram_mini = (Objeto*)malloc(sizeof(Objeto));
	memoria_ram_mini->imagem = al_load_bitmap("imagens/memoria_ram_mini.png");
	memoria_ram_mini->largura = 36;
	memoria_ram_mini->altura = 22;
	memoria_ram_mini->x = 90;
	memoria_ram_mini->y = 110;

	frame2 = al_create_sub_bitmap(sprite_parado->imagem, (sprite_parado->largura / 11) * i, 0, sprite_parado->largura / 11, sprite_parado->altura);


	// Variaveis de controle de menu
	int menu = 1, jogar = 0, creditos = 0, infos = 0, jogo = 1, tocando = 1, morreu = 0, venceu = 0, morreu_cena = 0, controles = 0;
	int atributoss = 0;
	bool clique_velocidade = false, clique_vida = false, clique_ataque = false;
	int teste = 1;
	int introducao = 0;
	int contador = 0;

	yInicial1 = inimigo1_mapa2->y;
	yInicial2 = inimigo2_mapa2->y;

	al_start_timer(timer);
	al_start_timer(frametimer);

	//	LOOPING PRINCIPAL
	while (jogo == 1) {
		//printf para testar o valor das variaveis (um facilitador para fazer o jogo)
		/*
		printf("BOSS: %d\n\n", chefao);
		printf("JOGAR: %d\n\n", jogar);
		printf("Boss Ataque: %d\n\n", chefao_ataque);
		printf("Boss espada: %d\n\n", chefao_espada);
		printf("Mapa: %d\n\n", mapa_atual);
		*/

		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		al_get_keyboard_state(&key_state);

		// Funcao do menu do jogo
		// Ja come�a com 1 pois ela ir� controlar os demais whiles, as outras op��es

		//abre o menu
		if (menu == 1) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(background, 0, 0, 0);
			al_flip_display();

			if (tocando == 1) {
				al_play_sample_instance(songInstance);
			}
			else if (tocando == 0)
				al_stop_sample_instance(songInstance);

			// Se o evento for um clique do mouse
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				// Se o clique foi no bot�o sair
				if ((evento.mouse.x >= 590 &&
					evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
					evento.mouse.y >= 6)) {

					// Fecha o jogo
					menu = 0;
					jogo = 0;
				}
				// Se for em jogar
				else if ((evento.mouse.x >= 185 &&
					evento.mouse.x <= 327 && evento.mouse.y <= 229 &&
					evento.mouse.y >= 178)) {

					al_stop_sample_instance(songInstance);
					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu = 0;
					// Inicia a fun��o jogar
					introducao = 1;
					//jogar = 1;

					al_draw_bitmap(img8, 0, 0, NULL);
					al_flip_display();
				}
				// Se for em infos
				else if ((evento.mouse.x >= 213 &&
					evento.mouse.x <= 402 && evento.mouse.y <= 298 &&
					evento.mouse.y >= 239)) {
					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu = 0;
					infos = 1;
				}
				// Se for em creditos
				else if ((evento.mouse.x >= 210 &&
					evento.mouse.x <= 405 && evento.mouse.y <= 390 &&
					evento.mouse.y >= 330)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu = 0;
					creditos = 1;
				}
				//se for em controles
				else if ((evento.mouse.x >= 278 &&
					evento.mouse.x <= 424 && evento.mouse.y <= 461 &&
					evento.mouse.y >= 408)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu = 0;
					controles = 1;
				}
				// se for em atributos
				else if ((evento.mouse.x >= 332 &&
					evento.mouse.x <= 487 && evento.mouse.y <= 228 &&
					evento.mouse.y >= 179)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					menu = 0;
					atributoss = 1;
				}
				// Se for em mutar som
				else if ((evento.mouse.x >= 538 &&
					evento.mouse.x <= 582 && evento.mouse.y <= 44 &&
					evento.mouse.y >= 7)) {


					//mutar e desmutar funcionando
					if (tocando == 1) {
						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						tocando = 0;
					}

					else {
						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						tocando = 1;
					}

				}

			}

		}
		else if (introducao == 1) {

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				

				if ((evento.mouse.x >= 1 &&
					evento.mouse.x <= 640 && evento.mouse.y <= 480 &&
					evento.mouse.y >= 1)) {
					contador ++;

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				if (contador == 1) {
					al_draw_bitmap(img9, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 2) {
					al_draw_bitmap(img6, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 3) {
					al_draw_bitmap(img7, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 4) {
					al_draw_bitmap(img7, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 5) {
					al_draw_bitmap(img2, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 6) {
					al_draw_bitmap(img3, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 7) {
					al_draw_bitmap(img4, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 8) {
					al_draw_bitmap(img5, 0, 0, 0);
					al_flip_display();
				}
				if (contador == 9) {
					introducao = 0;
					jogar = 1;
					al_draw_bitmap(background, 0, 0, 0);
					al_flip_display();
				}

			}
		}
		//inicia o jogo
		else if (jogar == 1) {

			//al_destroy_bitmap(img0);
			// MAPAS //
			if (mapa_atual == 1 && !colisao(personagem->x, personagem->y, 0, Chao, personagem->largura / 10, personagem->altura, tileSize, tileSize, 640) == 1 && !colisao(personagem->x, personagem->y, tileSize * 4 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 4 - 50, 0, 0) && !(mapa_atual == 1 && colisao(personagem->x, personagem->y, tileSize * 0 + 30, tileSize * 4, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0)) && !colisao(personagem->x, personagem->y, tileSize * 3 + 30, tileSize * 2, personagem->largura / 10, personagem->altura, tileSize * 3 - 50, 0, 0)) {
				caindo = 1;
			}
			else if (mapa_atual == 2 && !colisao(personagem->x, personagem->y, 0, Chao, personagem->largura / 10, personagem->altura, tileSize, tileSize, 640) == 1 && !colisao(personagem->x, personagem->y, tileSize * 0 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 3 - 50, 0, 0) && (!colisao(personagem->x, personagem->y, tileSize * 5 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0)) && !colisao(personagem->x, personagem->y, tileSize * 9 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0) && !colisao(personagem->x, personagem->y, tileSize * 1 + 30, tileSize * 3, personagem->largura / 10, personagem->altura, tileSize * 9 - 50, 0, 0)) {
				caindo = 1;
			}
			else if (mapa_atual == 3 && !colisao(personagem->x, personagem->y, 0, Chao, personagem->largura / 10, personagem->altura, tileSize, tileSize, 640) == 1 && !colisao(personagem->x, personagem->y, tileSize * 1 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0) && !colisao(personagem->x, personagem->y, tileSize * 3 + 30, tileSize * 3, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0) && !colisao(personagem->x, personagem->y, tileSize * 5 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0)) {

				caindo = 1;
			}
			else {
				caindo = 0;
				pulando = 0;
			}
			//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
						//colisao do personagem com o chao
			if (colisao(personagem->x, personagem->y, 0, Chao, personagem->largura / 10, personagem->altura, tileSize, tileSize, 640) == 1) {
				personagem->y = Chao - personagem->altura;
			}
			//colisao no mapa 1 
			if (mapa_atual == 1 && colisao(personagem->x, personagem->y, tileSize * 4 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 4 - 50, 0, 0)) {
				personagem->y = tileSize * 5 - personagem->altura;
			}
			if (mapa_atual == 1 && colisao(personagem->x, personagem->y, tileSize * 0 + 30, tileSize * 4, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0)) {
				personagem->y = tileSize * 4 - personagem->altura;
			}
			if (mapa_atual == 1 && colisao(personagem->x, personagem->y, tileSize * 3 + 30, tileSize * 2, personagem->largura / 10, personagem->altura, tileSize * 3 - 50, 0, 0)) {
				personagem->y = tileSize * 2 - personagem->altura;
			}

			//colisao com os 2 primeiros inimigos
			if (inimigo1 && (personagem->x <= goblin->x + 20) && (personagem->x + 20 >= goblin->x) && (personagem->y + personagem->altura >= goblin->y) && (personagem->y <= goblin->y + goblin->altura)) {
				jogar = 0;
				menu = 0;
				morreu = 1;
				//menu = 1;
				//inimigo1 = false;
			}
			if (inimigo2 && (personagem->x <= goblin2->x + 20) && (personagem->x + 20 >= goblin2->x) && (personagem->y + personagem->altura >= goblin2->y) && (personagem->y <= goblin2->y + goblin2->altura)) {
				jogar = 0;
				morreu = 1;

				//inimigo2 = false;
			}
			//colisao com o drop do processador (eh desenhada uma miniatura do processador)
			if ((personagem->x <= processador->x + processador->largura) && (personagem->x + personagem->largura / 10 >= processador->x) && (personagem->y - personagem->altura >= processador->y - processador->altura)) {
				al_play_sample(pegar_item, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				processador->y = 1000, processador->x = 1000;

				item_processador = false;
				item_processador_mini = true;
			}
			//colisao da espada com o inimigo
			if (inimigo1 && espada_ativa && (espada->x + 50 >= goblin->x) && (espada->x <= goblin->x + 20) && (espada->y >= goblin->y) && (espada->y <= goblin->y + goblin->altura)) {
				espada_ativa = false;
				espada->x = personagem->x;
				goblin->vida--;

				if (k == 0) {
					goblin->x += 10;
				}
				else if (k == 1) {
					goblin->x -= 10;
				}
			}

			if (inimigo1) {

				if (goblin->vida <= 0) {
					inimigo1 = false;
					espada_ativa = false;
					espada->x = personagem->x;
					item_processador = true;
					processador->x = goblin->x;
				}
			}
			//colisao da espada com o inimigo 2
			if (inimigo2 && espada_ativa && (espada->x + 50 >= goblin2->x) && (espada->x <= goblin2->x + 20) && (espada->y >= goblin2->y) && (espada->y <= goblin2->y + goblin2->altura)) {
				espada_ativa = false;
				espada->x = personagem->x;
				goblin2->vida--;
				if (l == 1) {
					goblin2->x += 10;
				}
				else if (l == 0) {
					goblin2->x -= 10;
				}
			}

			if (inimigo2) {

				if (goblin2->vida <= 0) {
					inimigo2 = false;
					espada_ativa = false;
					espada->x = personagem->x;
					item_placa = true;
					placa_mae->x = goblin2->x;
					placa_mae->y = goblin2->y;
				}
			}
			//?
			if ((espada->x >= 620) || (espada->x <= 0)) {
				espada_ativa = false;
				espada->x = personagem->x;
			}
			//verifica se o inimigo esta morto
			//dropa o item na posicao que ele morreu
			if (!inimigo2 && (personagem->x <= placa_mae->x + placa_mae->largura) && (personagem->x + personagem->largura / 10 >= placa_mae->x) && (personagem->y + personagem->altura >= placa_mae->y) && (personagem->y <= placa_mae->y + placa_mae->altura)) {

				al_play_sample(pegar_item, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				placa_mae->y = 1000, placa_mae->x = 1000;
				item_placa = false;

				item_placa_mini = true;
			}
			//verifica se o inimigo esta morto
			//dropa o item na posicao que ele morreu
			if (!inimigo1 && !inimigo2 && item_placa_mini && item_processador_mini && mapa_atual == 1) {
				portal_ativo = true;
				if (personagem->x + personagem->largura / 10 >= 560 && personagem->y + personagem->altura >= portal->y && personagem->y <= portal->y + portal->altura) {
					portal_ativo = false;
					mapa_atual = 2;
					personagem->x = 20;
					personagem->y = 75;
				}
			}

			if (item_processador_mini) {
				processador->x = 1000, processador->y = 1000;
			}
			if (item_placa_mini) {
				placa_mae->x = 1000, placa_mae->y = 1000;
			}



			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
						// MAPA2
			if (mapa_atual == 2) {


				// Colisao com plataforma grande
				// x do personagem // y do personagem // tamanho do x do obj // tamanho do y// largura/10 pq personagem tem 10 sprites// altura persomagem// quantidade de blocos
				if (colisao(personagem->x, personagem->y, tileSize * 1 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 3 - 105, 0, 0)) {
					personagem->y = tileSize * 5 - personagem->altura;
				}
				// plataforma pequena meio
				// tilesize * x depois tile size * y
				else if (colisao(personagem->x, personagem->y, tileSize * 5 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0)) {
					personagem->y = tileSize * 5 - personagem->altura;
				}
				//plataforma pequena direita
				else if (colisao(personagem->x, personagem->y, tileSize * 9 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 2 - 50, 0, 0)) {
					personagem->y = tileSize * 5 - personagem->altura;
				}
				// plataforma grande de cima
				else if (colisao(personagem->x, personagem->y, tileSize * 1 + 30, tileSize * 3, personagem->largura / 10, personagem->altura, tileSize * 9 - 50, 0, 0)) {
					personagem->y = tileSize * 3 - personagem->altura;
				}

				if (inimigo3) {

					if (inimigo1_mapa2->vida <= 0) {
						inimigo3 = false;
						espada_ativa = false;
						espada->x = personagem->x;
						item_memoria_ram = true;
						memoria_ram->x = inimigo1_mapa2->x;
						memoria_ram->y = inimigo1_mapa2->y + 20;
					}
				}

				if (!inimigo3 && (personagem->x <= memoria_ram->x + memoria_ram->largura) && (personagem->x + personagem->largura / 10 >= memoria_ram->x) && (personagem->y - personagem->altura >= memoria_ram->y - memoria_ram->altura)) {
					item_memoria_ram = false;
					al_play_sample(pegar_item, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					memoria_ram->x = 1000;
					memoria_ram->y = 1000;
					item_memoria_ram_mini = true;
				}

				if (inimigo4) {

					if (inimigo2_mapa2->vida <= 0) {
						chave->x = inimigo2_mapa2->x;
						chave->y = inimigo2_mapa2->y + 20;
						item_chave = true;
						inimigo4 = false;
						espada_ativa = false;
						espada->x = personagem->x;
					}
				}

				if (!inimigo4 && (personagem->x <= chave->x + chave->largura) && (personagem->x + personagem->largura / 10 >= chave->x) && (personagem->y + personagem->altura >= chave->y) && (personagem->y <= chave->y + chave->altura)) {
					item_chave = false;
					item_chave_mini = true;
					al_play_sample(pegar_item, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					chave->x = 1000;
					chave->y = 1000;
					pegou_chave = true;
				}

				if (inimigo3 && espada_ativa && (espada->x + 50 >= inimigo1_mapa2->x) && (espada->x <= inimigo1_mapa2->x + 20) && (espada->y >= inimigo1_mapa2->y) && (espada->y <= inimigo1_mapa2->y + inimigo1_mapa2->altura)) {
					espada_ativa = false;
					espada->x = personagem->x;
					inimigo1_mapa2->vida--;
					if (l == 1) {
						inimigo1_mapa2->x += 10;
					}
					else if (l == 0) {
						inimigo1_mapa2->x -= 10;
					}
				}
				if (inimigo4 && espada_ativa && (espada->x + 50 >= inimigo2_mapa2->x) && (espada->x <= inimigo2_mapa2->x + 20) && (espada->y >= inimigo2_mapa2->y) && (espada->y <= inimigo2_mapa2->y + inimigo2_mapa2->altura)) {
					espada_ativa = false;
					espada->x = personagem->x;
					inimigo2_mapa2->vida--;
					if (l == 1) {
						inimigo2_mapa2->x += 10;
					}
					else if (l == 0) {
						inimigo2_mapa2->x -= 10;
					}
				}

				if (inimigo3 && (personagem->x <= inimigo1_mapa2->x + 20) && (personagem->x + 20 >= inimigo1_mapa2->x) && (personagem->y + personagem->altura >= inimigo1_mapa2->y) && (personagem->y <= inimigo1_mapa2->y + inimigo1_mapa2->altura)) {
					jogar = 0;
					morreu = 1;
				}
				if (inimigo4 && (personagem->x <= inimigo2_mapa2->x + 20) && (personagem->x + 20 >= inimigo2_mapa2->x) && (personagem->y + personagem->altura >= inimigo2_mapa2->y) && (personagem->y <= inimigo2_mapa2->y + inimigo2_mapa2->altura)) {
					jogar = 0;
					morreu = 1;
				}


			}


			if (mapa_atual == 2 && item_memoria_ram_mini && pegou_chave && personagem->x >= 581 && personagem->y + personagem->altura >= 412) {
				personagem->x = 20;
				personagem->y = 75;
				mapa_atual = 3;

			}


			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
						//MAPA3
						//COLISOES E CONDICOES 
			if (mapa_atual == 3) {
				//x = 0 y = 
				if (colisao(personagem->x, personagem->y, tileSize * 1 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0)) {
					personagem->y = tileSize * 5 - personagem->altura;
				}
				else if (colisao(personagem->x, personagem->y, tileSize * 3 + 30, tileSize * 3, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0)) {
					personagem->y = tileSize * 3 - personagem->altura;
				}
				else if (colisao(personagem->x, personagem->y, tileSize * 5 + 30, tileSize * 5, personagem->largura / 10, personagem->altura, tileSize * 1 - 50, 0, 0)) {
					personagem->y = tileSize * 5 - personagem->altura;
				}

				if (boss->vida > 0 && personagem->y > 80) {
					chefao = true;
				}

				if (chefao && (personagem->x <= boss->x + 20) && (personagem->x + 20 >= boss->x) && (personagem->y + personagem->altura >= boss->y) && (personagem->y <= boss->y + boss->altura)) {
					jogar = 0;
					morreu = 1;
				}
				if (chefao && espada_ativa && (espada->x + 50 >= boss->x) && (espada->x <= boss->x + 20) && (espada->y >= boss->y) && (espada->y <= boss->y + boss->altura)) {
					espada_ativa = false;
					espada->x = personagem->x;
					boss->vida--;
				}
				if (chefao) {
					if (boss->vida <= 0) {
						chefao = false;
						chefao_ataque = false;
						chefao_espada = false;
						item_placa_de_video = true;
						placa_de_video->x = boss->x;

					}
					if (boss_sword->x + 100 <= 0) {
						chefao_espada = false;
						boss_sword->x = boss->x + 50;
					}
					if (chefao_espada && boss_sword->x <= personagem->x + personagem->largura / 10 && boss_sword->x >= personagem->x && boss_sword->y <= personagem->y + personagem->altura && boss_sword->y >= personagem->y) {
						chefao_espada = false;
						jogar = 0;
						morreu = 1;
					}
				}
				if (!chefao && (personagem->x <= placa_de_video->x + placa_de_video->largura) && (personagem->x + personagem->largura / 10 >= placa_de_video->x) && (personagem->y + personagem->altura >= placa_de_video->y) && (personagem->y <= placa_de_video->y + placa_de_video->altura)) {
					al_play_sample(pegar_item, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					placa_de_video->y = 1000, placa_de_video->x = 1000;
					item_placa_de_video = false;
					item_placa_de_video_mini = true;


					
					//descricao_placa_de_video = true;

					//venceu = 1;
					//jogar = 0;
				}

				if (mapa_atual == 3 && item_placa_de_video_mini && personagem->x >= 576 && personagem->y + personagem->altura >= 396) {
					venceu = 1;
					jogar = 0;

				}

			}


			if (evento.type == ALLEGRO_EVENT_TIMER) {

				movimentacao(evento);

				if (pressionando == 1 || pressionando == 0) {
					if (evento.timer.source == frametimer) {


						if (mapa_atual == 1) {
							al_draw_bitmap(background_jogo1, 0, 0, NULL);
							desenhar_mapa(map1);
						}
						if (mapa_atual == 2) {
							al_draw_bitmap(background2, 0, 0, NULL);
							desenhar_mapa(map2);
						}
						if (mapa_atual == 3 && !item_placa_de_video_mini) {
							al_draw_bitmap(background3, 0, 0, NULL);
							desenhar_mapa(map3);
						}
						if (mapa_atual == 3 && item_placa_de_video_mini) {
							al_draw_bitmap(background33, 0, 0, NULL);
							desenhar_mapa(map3);
						}
						
					}
					desenha(evento);


					al_flip_display();

				}
				else {
					al_draw_bitmap(background2, 0, 0, NULL);

					desenha(evento);

					if (mapa_atual == 1) {
						desenhar_mapa(map1);
					}
					if (mapa_atual == 2) {
						desenhar_mapa(map2);
					}
					if (mapa_atual == 3) {
						desenhar_mapa(map3);
					}

					al_flip_display();
				}
			}
			if (inventarioo) {

				if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

					if ((evento.mouse.x >= 122 &&
						evento.mouse.x <= 211 && evento.mouse.y <= 299 &&
						evento.mouse.y >= 209) && item_processador_mini) {

						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						descricao_processador = true;
					}
					if ((evento.mouse.x >= 227 &&
						evento.mouse.x <= 317 && evento.mouse.y <= 299 &&
						evento.mouse.y >= 219) && item_placa_mini) {

						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						descricao_placa_mae = true;
					}
					if ((evento.mouse.x >= 327 &&
						evento.mouse.x <= 416 && evento.mouse.y <= 302 &&
						evento.mouse.y >= 210) && item_memoria_ram_mini) {
						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						descricao_memoria_ram = true;
					}
					if ((evento.mouse.x >= 427 &&
						evento.mouse.x <= 517 && evento.mouse.y <= 300 &&
						evento.mouse.y >= 209) && item_placa_de_video_mini) {


						al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						descricao_placa_de_video = true;
					}



				}
				else if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)) {
					descricao_processador = false;
					descricao_placa_mae = false;
					descricao_placa_de_video = false;
					descricao_memoria_ram = false;
					/*if (descricao_placa_de_video == false) {
						al_draw_bitmap(venceu1, 0, 0, 0);
						al_flip_display();
					}*/
				}
			}



		}
		else if (morreu == 1) {

			al_draw_bitmap(morreu1, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 1 &&
					evento.mouse.x <= 640 && evento.mouse.y <= 480 &&
					evento.mouse.y >= 1)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					jogo = 0;

					//jogo = 0;
				}
			}

		}
		else if (venceu == 1) {
			al_draw_bitmap(venceu1, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 1 &&
					evento.mouse.x <= 640 && evento.mouse.y <= 480 &&
					evento.mouse.y >= 1)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					jogo = 0;
					//jogo = 0;
				}
			}
		}
		// Se clicar em creditos
		else if (creditos == 1) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(creditoss, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 590 &&
					evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
					evento.mouse.y >= 6)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					creditos = 0;
					menu = 1;
				}
			}
		}
		// Se clicar em infos
		else if (infos == 1) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(infoss, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 590 &&
					evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
					evento.mouse.y >= 6)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					infos = 0;
					menu = 1;
				}

			}

		}
		//controles do jogo no menu
		else if (controles == 1) {


			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(controless, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 590 &&
					evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
					evento.mouse.y >= 6)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

					controles = 0;
					menu = 1;
				}

			}
		}
		//atributos no menu
		else if (atributoss) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(atributos, 0, 0, 0);
			al_flip_display();

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 47 &&
					evento.mouse.x <= 141 && evento.mouse.y <= 209 &&
					evento.mouse.y >= 128)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);


					velocidade_movimento = 6.5;
					velocidade_projetil = 13.0;

					goblin->vida = 6;
					goblin2->vida = 5;
					inimigo1_mapa2->vida = 4;
					inimigo2_mapa2->vida = 6;
					atributoss = 0;
					menu = 1;

				}

			}
			// vida
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 45 &&
					evento.mouse.x <= 142 && evento.mouse.y <= 317 &&
					evento.mouse.y >= 234)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);



					velocidade_projetil = 13.0;
					velocidade_movimento = 4.5;

					goblin->vida = 5;
					goblin2->vida = 4;
					inimigo1_mapa2->vida = 3;
					inimigo2_mapa2->vida = 5;

					atributoss = 0;
					menu = 1;

				}

			}
			//velocidade projetil
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 45 &&
					evento.mouse.x <= 142 && evento.mouse.y <= 425 &&
					evento.mouse.y >= 339)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

					velocidade_projetil = 15.0;

					velocidade_movimento = 4.5;
					goblin->vida = 6;
					goblin2->vida = 5;
					inimigo1_mapa2->vida = 4;
					inimigo2_mapa2->vida = 6;

					atributoss = 0;
					menu = 1;

				}

			}
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

				if ((evento.mouse.x >= 590 &&
					evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
					evento.mouse.y >= 6)) {

					al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					atributoss = 0;
					menu = 1;
				}
			}

		}


		// Se for no x da janela
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			jogo = 0;
		}

	}

	//destroy de bitmaps
	al_destroy_display(janela);
	al_destroy_bitmap(background);
	al_destroy_bitmap(chao);
	al_destroy_bitmap(chao_fim);
	al_destroy_bitmap(plataforma1);
	al_destroy_bitmap(creditoss);
	al_destroy_bitmap(infoss);
	al_destroy_bitmap(frame);
	al_destroy_bitmap(frame2);
	al_destroy_bitmap(personagem->imagem);
	al_destroy_bitmap(sprite_atacando->imagem);
	al_destroy_bitmap(sprite_parado->imagem);
	al_destroy_bitmap(processador_mini->imagem);
	al_destroy_bitmap(processador->imagem);
	al_destroy_event_queue(fila_eventos);
	al_destroy_font(fonte);
	al_destroy_bitmap(inventario->imagem);
	al_destroy_bitmap(goblin->imagem);
	al_destroy_bitmap(goblin2->imagem);
	al_destroy_bitmap(boss->imagem);
	al_destroy_bitmap(boss_sword->imagem);
	al_destroy_bitmap(espada->imagem);
	al_destroy_bitmap(inimigo1_mapa2->imagem);
	al_destroy_bitmap(inimigo2_mapa2->imagem);
	al_destroy_timer(timer);
	al_destroy_timer(frametimer);
	al_destroy_bitmap(chao2);
	al_destroy_bitmap(chao2_fim);
	al_destroy_bitmap(img0);
	al_destroy_bitmap(img7);
	al_destroy_bitmap(img8);
	al_destroy_bitmap(img9);
	al_destroy_bitmap(img1);
	al_destroy_bitmap(img2);
	al_destroy_bitmap(img3);
	al_destroy_bitmap(img4);
	al_destroy_bitmap(img5);
	al_destroy_bitmap(img6);
	al_destroy_bitmap(img10);

	//free da memoria
	free(goblin);
	free(personagem);
	free(sprite_atacando);
	free(sprite_parado);
	free(espada);
	free(processador_mini);
	free(processador);
	free(placa_de_video);
	free(placa_de_video_mini);
	free(placa_mae);
	free(placa_mae_mini);
	free(inventario);
	free(memoria_ram);
	free(memoria_ram_mini);
	free(boss);
	free(boss_sword);

	return 0;
}