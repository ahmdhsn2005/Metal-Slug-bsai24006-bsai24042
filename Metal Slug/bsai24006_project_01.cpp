#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/raymath.h"
#include<iostream>

//Repo Link: 

#define Width 640
#define Height 480
//Musab and Cheema (structs toh mil kr hi bnane the obv)
struct bullet
{
    int x, y, direction;
    bool active;
    char tag;
};

struct time_based
{
    int allowed_runs_per_second = 1;
    clock_t last_time = clock();
    int time_delta = (CLOCKS_PER_SEC / allowed_runs_per_second);
};


struct entity
{
    int ix = 0;
    Rectangle   foot,
        left_arm,
        right_arm;
    int health;
    int ammo;
    int gravity;

    time_based weapon;

    int direction;

    time_based animation;

    int animation_index = 0;

    void (*physics_engine)(entity&);

    bool is_running = false;
    bool is_shooting = false;


    int shift = 0;

    bool alive = true;
    bullet mag[100] = {};


};

void player_core(entity& player);
void enemy_core(entity& player);
void heli_core(entity& heli);



//all entity initializations
//Musab
entity cheema = { 0,{20,100,40,10},{10,40,10,60},{60,40,10,60},100,100,0,{3},1,{1},0,&player_core };


//Cheema 
entity musabs[5] = { {400,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1 ,{11},0,&enemy_core},
                    {650,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core },
                    {750,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core },
                    {970,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1 ,{11},0,&enemy_core},
                    {1300,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core} };

entity musabs1[3] = { {1987,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core},
                    {2287,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core},
                    {1698,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1 ,{11},0,&enemy_core} };

entity musabs2[2] = { {3600,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11},0,&enemy_core },
                    {3122,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11} ,0,&enemy_core} };

entity musabs3[3] = { {4835,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11} ,0,&enemy_core},
                    {4588,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11} ,0,&enemy_core},
                    {4357,{0,100,40,10},{0,40,10,60},{0,40,10,60},10,10,0,{1},-1,{11} ,0,&enemy_core} };

entity heli = { 3184,{20,100,40,10},{10,40,10,60},{60,40,10,60},50,100,0,{2},-2,{1},0,&heli_core };


int bdx = 0;

Sound scream = LoadSound("scream.mp3");

//Cheema
Rectangle C1 = { bdx, 341, 1336, 200 };
Rectangle C2 = { bdx + 1336, 440, 2436, 79 };
Rectangle C3 = { bdx + 3772, 425, 2796, 100 };
Rectangle C4 = { bdx + 1752, 320,69,22 };
Rectangle C5 = { bdx + 1860,240,228,22 };
Rectangle C8 = { bdx + 2263, 330, 85, 22 };
Rectangle C9 = { bdx + 3097, 330, 78, 22 };
Rectangle C10 = { bdx + 4073, 353, 76, 14 };
Rectangle C12 = { bdx + 4149, 273, 140, 22 };
Rectangle C13 = { bdx + 4524, 273, 150, 22 };
Rectangle C14 = { bdx + 4689, 187, 104, 22 };
Rectangle C15 = { bdx + 4793, 170, 283, 22 };
Rectangle C16 = { bdx + 4315, 170, 86, 22 };

Rectangle C17 = { Width / 2 - 20, 0, 15, Height };
Rectangle C18 = { 60, 0, 15, Height };



//Cheema
void firebullet(int player_x, int player_y, int direction, char tag, bullet mag[])
{
    for (int i = 0; i < 100; i++)
    {
        if (mag[i].active == false)
        {
            mag[i].x = player_x + 10;
            mag[i].y = player_y - 10;
            mag[i].direction = direction;
            mag[i].active = true;
            mag[i].tag = tag;
            break;
        }
    }
}
//Cheema
void updatebullet(bullet mag[])
{
    for (int i = 0; i < 100; i++)
    {
        if (mag[i].active)
        {
            if (mag[i].direction == 1)
                mag[i].x += 15;
            else if (mag[i].direction == -1)
                mag[i].x -= 15;
            else if (mag[i].direction == 2)
            {
                mag[i].y -= 15;
            }
            else if (mag[i].direction == -2)
            {
                mag[i].y += 15;
            }

            if (mag[i].x < 0 or mag[i].x > Width)
                mag[i].active = false;
        }
    }
}
//Cheema
void drawbullet(bullet mag[], Texture2D blt)
{
    blt.width = 20;
    blt.height = 20;
    for (int i = 0; i < 100; i++)
    {
        if (mag[i].active)
        {
            DrawTexture(blt, mag[i].x, mag[i].y, WHITE);
        }
    }
}

//Musab (Musab ki math achi hai)
void delta_cal(entity& player, int delta)
{
    player.foot.y -= delta;
    player.left_arm.y -= delta;
    player.right_arm.y -= delta;
}
//Musab
void collider_y_setter(entity& player)
{
    int delta = 0;

    if ((CheckCollisionRecs(C1, player.foot)))
        delta = player.foot.y - 331;
    else  if ((CheckCollisionRecs(C2, player.foot)))
        delta = player.foot.y - 440;
    else  if ((CheckCollisionRecs(C3, player.foot)))
        delta = player.foot.y - 425;
    else  if ((CheckCollisionRecs(C4, player.foot)))
        delta = player.foot.y - 320;
    else  if ((CheckCollisionRecs(C5, player.foot)))
        delta = player.foot.y - 240;
    else  if ((CheckCollisionRecs(C8, player.foot)))
        delta = player.foot.y - 330;
    else  if ((CheckCollisionRecs(C9, player.foot)))
        delta = player.foot.y - 330;
    else  if ((CheckCollisionRecs(C10, player.foot)))
        delta = player.foot.y - 353;
    else  if ((CheckCollisionRecs(C12, player.foot)))
        delta = player.foot.y - 273;
    else  if ((CheckCollisionRecs(C13, player.foot)))
        delta = player.foot.y - 273;
    else  if ((CheckCollisionRecs(C14, player.foot)))
        delta = player.foot.y - 187;
    else  if ((CheckCollisionRecs(C15, player.foot)))
        delta = player.foot.y - 170;
    else  if ((CheckCollisionRecs(C16, player.foot)))
        delta = player.foot.y - 170;

    delta_cal(player, delta);
}
//Musab
bool all_collider_condition(Rectangle collider)
{
    return (CheckCollisionRecs(C1, collider) or CheckCollisionRecs(C2, collider) or CheckCollisionRecs(C3, collider) or
        CheckCollisionRecs(C4, collider) or CheckCollisionRecs(C5, collider) or CheckCollisionRecs(C8, collider) or
        CheckCollisionRecs(C9, collider) or CheckCollisionRecs(C10, collider) or CheckCollisionRecs(C12, collider) or
        CheckCollisionRecs(C13, collider) or CheckCollisionRecs(C14, collider) or CheckCollisionRecs(C15, collider) or
        CheckCollisionRecs(C16, collider));
}
//Musab
void bullet_collision(entity& player, bullet mag[])
{
    for (int index = 0; index < 100; index++)
    {
        if ((CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, player.foot) or
            CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, player.left_arm) or
            CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, player.right_arm)) and
            mag[index].active == true && mag[index].tag != 'P')
        {
            player.health -= 3;
            mag[index].active = false;
        }
    }
}

//Cheema
void check_enemy_hit(entity& enemy, bullet mag[])
{
    
    if (!enemy.alive) return;

    for (int index = 0; index < 100; index++)
    {
        if ((CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, enemy.foot) or
            CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, enemy.left_arm) or
            CheckCollisionCircleRec({ (float)mag[index].x,(float)mag[index].y, }, 3, enemy.right_arm)) and
            mag[index].active == true && mag[index].tag == 'P')
        {
            enemy.health -= 5;
            mag[index].active = false;
        }
        if (enemy.health <= 0)
        {
            enemy.alive = false;
            PlaySound(scream);
        }
    }
}
//Musab
void update_cal(entity& player)
{
    player.foot.x = bdx + 20 + player.ix + player.shift;
    player.left_arm.x = bdx + 10 + player.ix + player.shift;
    player.right_arm.x = bdx + 60 + player.ix + player.shift;
}
//Cheema
void update_enemies()
{
    for (int i = 0; i < 5; i++)
        update_cal(musabs[i]);
    for (int i = 0; i < 3; i++)
    {
        update_cal(musabs1[i]);
        update_cal(musabs3[i]);
    }
    for (int i = 0; i < 2; i++)
        update_cal(musabs2[i]);

    update_cal(heli);
}
//Musab
void gravity_cal(entity& player, int val)
{
    player.gravity += val;
    player.foot.y += player.gravity;
    player.left_arm.y += player.gravity;
    player.right_arm.y += player.gravity;
}
//Musab
void collider_affect_gravity(entity& player)
{
    if (!all_collider_condition(player.foot))
    {
        gravity_cal(player, 1);
    }

    if (all_collider_condition(player.foot))
    {
        player.gravity = 0;
    }
}
//Musab
void do_the_bullet_thing(entity& player)
{
    clock_t currentTime = clock();

    if (currentTime - player.weapon.last_time >= player.weapon.time_delta && player.ammo > 0)
    {
        firebullet(player.foot.x, player.foot.y - 40, player.direction, 'E', player.mag);
        player.weapon.last_time = currentTime;
        player.ammo--;
    }
}
//Musab
void do_shifiting_cal(entity& player, int shift, int dir)
{
    if (abs(cheema.foot.x - player.foot.x) < 400 && abs(cheema.foot.x - player.foot.x) > 150 and !all_collider_condition(player.right_arm))
    {
        player.shift += shift;
    }
    if (!all_collider_condition(player.right_arm))
    {
        player.direction = dir;
    }

}
//Musab
void state_setter(entity& player)
{
    if (abs(cheema.foot.x - player.foot.x) < 160)
        player.is_running = false;
    else
        player.is_running = true;
}
//Cheema
void enemy_core(entity& musabs)
{
    if (!musabs.alive)
        return;

    collider_affect_gravity(musabs);
    collider_y_setter(musabs);

    if ((cheema.foot.x > musabs.foot.x))
    {
        do_shifiting_cal(musabs, 5, 1);

        do_the_bullet_thing(musabs);

        state_setter(musabs);
    }
    else if ((cheema.foot.x < musabs.foot.x))
    {
        do_shifiting_cal(musabs, -5, -1);

        if (abs(cheema.foot.x - musabs.foot.x) < 400)
            do_the_bullet_thing(musabs);

        state_setter(musabs);

    }

    updatebullet(musabs.mag);
    bullet_collision(cheema, musabs.mag);
}
//Cheema
void allenemychecks()
{
    for (int i = 0; i < 5; i++)
    {
        check_enemy_hit(musabs[i], cheema.mag);
    }
    for (int i = 0; i < 3; i++)
    {
        check_enemy_hit(musabs1[i], cheema.mag);
        check_enemy_hit(musabs3[i], cheema.mag);
    }
    for (int i = 0; i < 2; i++)
    {
        check_enemy_hit(musabs2[i], cheema.mag);
    }

    for (int i = 0; i < 5; i++)
    {
        musabs[i].physics_engine(musabs[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        musabs1[i].physics_engine(musabs1[i]);
        musabs3[i].physics_engine(musabs3[i]);

    }for (int i = 0; i < 2; i++)
    {
        musabs2[i].physics_engine(musabs2[i]);
    }

}
//Cheema
void enemy_print(Texture2D enemy_running[], Texture2D enemy_running_flipped[], entity& player, Texture2D enemy_idle, Texture2D enemy_idle_flipped)
{

    clock_t currentTime = clock();

    if (currentTime - player.animation.last_time >= player.animation.time_delta and player.is_running and abs(cheema.foot.x - player.foot.x) < 400)
    {
        player.animation_index++;
        player.animation.last_time = currentTime;
    }

    if (player.is_running and player.alive and abs(cheema.foot.x - player.foot.x) < 400)
    {
        if (player.direction == -1)
            DrawTexture(enemy_running[player.animation_index], player.left_arm.x - 40, player.left_arm.y - 15, WHITE);
        if (player.direction == 1)
            DrawTexture(enemy_running_flipped[player.animation_index], player.left_arm.x - 40, player.left_arm.y - 15, WHITE);
    }
    else
    {
        if (player.direction == -1)
            DrawTexture(enemy_idle, player.left_arm.x - 40, player.left_arm.y - 25, WHITE);
        if (player.direction == 1)
            DrawTexture(enemy_idle_flipped, player.left_arm.x - 40, player.left_arm.y - 25, WHITE);
    }

    if (player.animation_index > 10 and player.is_running)
        player.animation_index = 0;
}
//Cheema
void heli_print(Texture2D heli_frames[], entity& heli)
{
    clock_t currentTime = clock();

    if (currentTime - heli.animation.last_time >= heli.animation.time_delta / 2)
    {
        heli.animation_index = (heli.animation_index + 1) % 3;
        heli.animation.last_time = currentTime;
    }

    DrawTextureEx(heli_frames[heli.animation_index], { heli.left_arm.x - 20,heli.left_arm.y - 20 }, 0.0f, 3.0f, WHITE);
}
//Cheema
void drawenemies(Texture2D blt, Texture2D enemy_running[], Texture2D enemy_running_flipped[], Texture2D enemy_idle, Texture2D enemy_idle_flipped)
{
    for (int i = 0; i < 5; i++)
    {
        if (musabs[i].alive)
        {
            enemy_print(enemy_running, enemy_running_flipped, musabs[i], enemy_idle, enemy_idle_flipped);
            drawbullet(musabs[i].mag, blt);
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (musabs1[i].alive)
        {
            enemy_print(enemy_running, enemy_running_flipped, musabs1[i], enemy_idle, enemy_idle_flipped);
            drawbullet(musabs1[i].mag, blt);
        }

        if (musabs3[i].alive)
        {
            enemy_print(enemy_running, enemy_running_flipped, musabs3[i], enemy_idle, enemy_idle_flipped);
            drawbullet(musabs3[i].mag, blt);
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (musabs2[i].alive)
        {
            enemy_print(enemy_running, enemy_running_flipped, musabs2[i], enemy_idle, enemy_idle_flipped);
            drawbullet(musabs2[i].mag, blt);
        }
    }
}
//Musab
void player_cal(entity& player, int x, int dir)
{
    player.right_arm.x += x;
    player.left_arm.x += x;
    player.foot.x += x;
    player.direction = dir;
}
//Cheema and Musab
void player_core(entity& player)
{
    collider_affect_gravity(player);

    if (IsKeyPressed(KEY_SPACE) and all_collider_condition(player.foot))
    {
        gravity_cal(player, -20);
    }

    collider_y_setter(player);

    if (IsKeyDown(KEY_RIGHT) and CheckCollisionRecs(player.right_arm, C17) and bdx >= -5901)
    {
        bdx -= 10;
        player.is_running = true;
    }
    else if (IsKeyDown(KEY_RIGHT) and bdx >= -5901 and !all_collider_condition(player.right_arm))
    {
        player_cal(player, 10, 1);
        player.is_running = true;
    }

    if (IsKeyDown(KEY_LEFT) and CheckCollisionRecs(player.left_arm, C18) and bdx < 0)
    {
        bdx += 10;
        player.is_running = true;

    }
    else if (IsKeyDown(KEY_LEFT) and bdx < 0 and !all_collider_condition(player.left_arm))
    {
        player_cal(player, -10, -1);
        player.is_running = true;
    }


    if (IsKeyDown(KEY_UP))
    {
        player.direction = 2;
    }

    if (IsKeyDown(KEY_A) and player.ammo != 0)
    {
        clock_t currentTime = clock();
        if (currentTime - player.weapon.last_time >= player.weapon.time_delta && player.ammo > 0)
        {
            firebullet(player.foot.x, player.foot.y - 40, player.direction, 'P', player.mag);
            player.weapon.last_time = currentTime;
            player.ammo--;
        }

        player.is_shooting = true;
    }



}
//Cheema
void heli_core(entity& heli)
{
    if (!heli.alive)
        return;

    if ((cheema.foot.x > heli.foot.x))
    {
        if (abs(cheema.foot.x - heli.foot.x) < 400 && abs(cheema.foot.x - heli.foot.x) > 150)
            if (!all_collider_condition(heli.right_arm))
            {
                heli.shift += 5;
            }

        clock_t currentTime = clock();
        if (currentTime - heli.weapon.last_time >= heli.weapon.time_delta && heli.ammo > 0)
        {
            firebullet(heli.foot.x, heli.foot.y - 40, heli.direction, 'E', heli.mag);
            heli.weapon.last_time = currentTime;
            heli.ammo--;
        }
    }
    else if ((cheema.foot.x < heli.foot.x))
    {
        if (abs(cheema.foot.x - heli.foot.x) < 400 && abs(cheema.foot.x - heli.foot.x) > 150)
            if (!all_collider_condition(heli.left_arm))
            {
                heli.shift -= 5;

            }

        clock_t currentTime = clock();
        if (currentTime - heli.weapon.last_time >= heli.weapon.time_delta && heli.ammo > 0 and abs(cheema.foot.x - heli.foot.x) < 400)
        {
            firebullet(heli.foot.x, heli.foot.y - 40, heli.direction, 'E', heli.mag);
            heli.weapon.last_time = currentTime;
            heli.ammo--;
        }
    }

    updatebullet(heli.mag);
    bullet_collision(cheema, heli.mag);
    check_enemy_hit(heli, cheema.mag);
}

//Cheema and Musab
void metal_slug()
{
    Texture2D blt2 = LoadTexture("bullet2.png");
    Texture2D blt = LoadTexture("bullet.png");


    Texture2D bullet_extras = LoadTexture("bullet_extra.png");



    Texture2D bd = LoadTexture("L1.png");
    bd.height = Height + 225;



    int allowed_runs_per_second = 5;
    clock_t last_time = clock();
    int time_delta = (CLOCKS_PER_SEC / allowed_runs_per_second);


    Texture2D run[3] = { LoadTexture("run_1.png"),LoadTexture("run_3.png"),LoadTexture("run_2.png") };
    Texture2D run_flipped[3] = { LoadTexture("run_1_flipped.png"),LoadTexture("run_3_flipped.png"),LoadTexture("run_2_flipped.png") };

    Texture2D heli_anim[3] = { LoadTexture("heli_1.png"),LoadTexture("heli_2.png"),LoadTexture("heli_3.png") };

    Texture2D enemy_running[12] = {
        LoadTexture("assets/enemy/enemy_running_1.png"), LoadTexture("assets/enemy/enemy_running_2.png"),
        LoadTexture("assets/enemy/enemy_running_3.png"), LoadTexture("assets/enemy/enemy_running_4.png"),
        LoadTexture("assets/enemy/enemy_running_5.png"), LoadTexture("assets/enemy/enemy_running_6.png"),
        LoadTexture("assets/enemy/enemy_running_7.png"), LoadTexture("assets/enemy/enemy_running_8.png"),
        LoadTexture("assets/enemy/enemy_running_9.png"), LoadTexture("assets/enemy/enemy_running_10.png"),
        LoadTexture("assets/enemy/enemy_running_11.png"), LoadTexture("assets/enemy/enemy_running_12.png") };

    Texture2D enemy_running_flipped[12] = {
        LoadTexture("assets/enemy/enemy_running_1_flipped.png"), LoadTexture("assets/enemy/enemy_running_2_flipped.png"),
        LoadTexture("assets/enemy/enemy_running_3_flipped.png"), LoadTexture("assets/enemy/enemy_running_4_flipped.png"),
        LoadTexture("assets/enemy/enemy_running_5_flipped.png"), LoadTexture("assets/enemy/enemy_running_6_flipped.png"),
        LoadTexture("assets/enemy/enemy_running_7_flipped.png"), LoadTexture("assets/enemy/enemy_running_8_flipped.png"),
        LoadTexture("assets/enemy/enemy_running_9_flipped.png"), LoadTexture("assets/enemy/enemy_running_10_flipped.png"),
        LoadTexture("assets/enemy/enemy_running_11_flipped.png"), LoadTexture("assets/enemy/enemy_running_12_flipped.png") };


    Texture2D heavy_machine_gun_sprite = LoadTexture("assets/heavy_machine_gun.png");

    Texture2D enemy_idle = LoadTexture("enemy_idle.png");
    Texture2D enemy_idle_flipped = LoadTexture("enemy_idle.png");

    Texture2D idle = LoadTexture("idle.png");
    Texture2D idle_fliiped = LoadTexture("idle_flipped.png");



    Texture2D fire = LoadTexture("fire.png");
    Texture2D fire_flipped = LoadTexture("fire_flipped.png");




    Sound ffx = LoadSound("ffx.mp3");
    Sound level_1 = LoadSound("assets/audio/level_1.wav");
    Sound heavy_machine_gun_sound = LoadSound("assets/audio/heavy_machine_gun.mp3");

    PlaySound(level_1);

    bool has_heavy_machine_gun = false;

    int index = 0;

    Rectangle heavy_machine_gun = { bdx + 1915,190,50,50 };


    int jumpingCounter = 0;
    int jumpingFrameRate = 15;
    int jumpingFrame = 0;
    int numShootFrames = 3;

    heavy_machine_gun_sprite.height = heavy_machine_gun.height;
    heavy_machine_gun_sprite.width = heavy_machine_gun.width;

    while (!WindowShouldClose())
    {
        cheema.is_running = false;
        cheema.is_shooting = false;


        if (GetKeyPressed() == KEY_ESCAPE)
            break;

        C1.x = bdx;
        C2.x = bdx + 1336;
        C3.x = bdx + 3772;
        C4.x = bdx + 1752;
        C5.x = bdx + 1860;
        C8.x = bdx + 2263;
        C9.x = bdx + 3097;
        C10.x = bdx + 4073;
        C12.x = bdx + 4149;
        C13.x = bdx + 4524;
        C14.x = bdx + 4689;
        C15.x = bdx + 4793;
        C16.x = bdx + 4315;
        heavy_machine_gun.x = bdx + 1915;

        update_enemies();


        cheema.physics_engine(cheema);
        heli.physics_engine(heli);


        allenemychecks();
        updatebullet(cheema.mag);


        if (CheckCollisionRecs(cheema.right_arm, heavy_machine_gun) or CheckCollisionRecs(cheema.left_arm, heavy_machine_gun))
        {
            has_heavy_machine_gun = true;
            cheema.weapon.allowed_runs_per_second = 8;

            cheema.weapon.time_delta = (CLOCKS_PER_SEC / cheema.weapon.allowed_runs_per_second);
            PlaySound(heavy_machine_gun_sound);
            cheema.ammo = 99;
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawTexture(bd, bdx, -235, WHITE);



            drawenemies(blt, enemy_running, enemy_running_flipped, enemy_idle, enemy_idle_flipped);

            if (heli.alive)
            {

                drawbullet(heli.mag, blt2);
                heli_print(heli_anim, heli);
            }

            clock_t currentTime = clock();

            if (cheema.is_running)
            {
                jumpingCounter++;
                if (jumpingCounter >= (30 / jumpingFrameRate))
                {
                    jumpingCounter = 0;
                    jumpingFrame++;
                    if (jumpingFrame >= numShootFrames)
                    {
                        jumpingFrame = 0;
                    }
                }
            }


            if (cheema.is_running and cheema.is_shooting == false)
            {
                if (cheema.direction == 1)
                    DrawTextureEx(run[jumpingFrame], { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                else if (cheema.direction == -1)
                    DrawTextureEx(run_flipped[jumpingFrame], { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                else
                    DrawTextureEx(idle, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
            }
            else if (cheema.is_shooting)
            {

                if (cheema.direction == 1)
                    DrawTextureEx(fire, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                else if (cheema.direction == -1)
                    DrawTextureEx(fire_flipped, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                else
                    DrawTextureEx(idle, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);

            }
            else
            {
                if (cheema.direction == 1)
                    DrawTextureEx(idle, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                if (cheema.direction == -1)
                    DrawTextureEx(idle_fliiped, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);
                else
                    DrawTextureEx(idle, { (float)cheema.left_arm.x - 10,(float)cheema.right_arm.y - 10 }, 0.0f, 2.5f, WHITE);

            }




            DrawTextureEx(bullet_extras, { (float)0,(float)0 }, 0.0f, 2.5f, WHITE);
            DrawText(TextFormat("%d", cheema.ammo), 100, 5, 20, WHITE);


            DrawText(TextFormat("health: %d", cheema.health), 15, 22, 18, MAROON);


            if (!has_heavy_machine_gun)
                DrawTexture(heavy_machine_gun_sprite, heavy_machine_gun.x, heavy_machine_gun.y, WHITE);

            if (cheema.right_arm.x > C17.x)
            {
                DrawText("Raja Jeeee! You Found a Bug!", Width / 2, 0, 20, RED);
            }
            drawbullet(cheema.mag, blt);
        }


        EndDrawing();

        if (index > 4)
            index = 0;

        if (cheema.health <= 0)
            break;
    }

    Texture2D over = LoadTexture("gameover.png");
    while (!WindowShouldClose())
    {
        
        over.height = Height;
        over.width = Width;
        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawTexture(over, 0, 0, WHITE);
        }
        EndDrawing();
    }


    exit(1);
}

//Musab
int main()
{
    InitWindow(Width, Height, "Metal Slug");

    SetTargetFPS(30);


    Texture2D MM1 = LoadTexture("MM1.png");
    Texture2D MM2 = LoadTexture("MM2.png");


    MM1.height = Height;
    MM1.width = Width;
    MM2.height = Height;
    MM2.width = Width;

    InitAudioDevice();

    //ToggleFullscreen();



    bool coin = false;
    Sound coin_insert = LoadSound("new_coin.wav");
    Sound MM_Audio = LoadSound("MM_Audio.wav");

    PlaySound(MM_Audio);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SIX))
        {
            PlaySound(coin_insert);
            coin = true;
        }

        if (IsKeyPressed(KEY_A) and coin)
        {
            StopSound(MM_Audio);
            metal_slug();
        }




        BeginDrawing();
        {
            ClearBackground(WHITE);

            if (time(0) % 2 == 0)
            {
                DrawTexture(MM1, 0, 0, WHITE);
            }
            else {
                DrawTexture(MM2, 0, 0, WHITE);
            }


        }
        EndDrawing();
    }




}