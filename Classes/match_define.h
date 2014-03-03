//
//  match_define.h
//  RealSoccer
//
//  Created by ck02-216 on 1/9/14.
//
//

#ifndef RealSoccer_match_define_h
#define RealSoccer_match_define_h

typedef enum tagAxis
{
    X,
    Y,
    Z
}Axis;

//camera
//define the retio that perspective axis Z to axis Y
#define PERSPECTIVE_RATIO 0.5f

//ball
#define BALL_RADIUS 8.0f

//physics
//gravity
#define GRAVITY_ACC 8.0f
//resistance on ground
#define RESISTANCE_GROUND 2.0f
//resistance in air
#define RESISTANCE_AIR 1.0f
//ball bounce ratio on axis Z
#define BALL_BOUNCE_RATIO_ONGROUND 0.6f
//ball bounce ratio on axis Z
#define BALL_BOUNCE_RATIO_WITH_GOAL 0.6f
//minimum of speed effect value, less than this value then set zero.
#define MIN_SPEED_EFFECT_ZERO 1.0f

//ball indicator
//ball indicator max length
#define BALL_INDICATOR_MAX_LEN 80.0f
#define BALL_INDICATOR_WIDTH 8.0f
#define BALL_INDICATOR_TRIANGLE_WIDTH 10.0f

//ball force
#define BALL_FORCE_MIN_FACTOR 3.0f
#define BALL_FORCE_MAX_FACTOR 5.0f

//goal parameter
//coordinate on field.jpg
//left 240
//right 404
//top 970
//bottom 916
#define GOAL_LEFT 238.0f
#define GOAL_RIGHT 404.0f
#define GOAL_TOP 972.0f
#define GOAL_BOTTOM 918.0f
#define GOAL_NET_BOTTOM 944.0f
#define GOAL_POST_RADIUS 5.0f

#endif
