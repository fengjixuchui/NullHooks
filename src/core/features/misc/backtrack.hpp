#pragma once

#define TICK_INTERVAL			( interfaces::globals->interval_per_tick )
#define TIME_TO_TICKS( t )		( (int)( 0.5f + (float)( t ) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL * (float)( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * time_to_ticks( t ) )
#define TICK_NEVER_THINK		( -1 )

// Stores information about that tick
struct player_record {
	vec3_t head;
	float simulation_time;
	matrix_t matrix[128];
};

struct convars {
	convar* update_rate;
	convar* max_update_rate;
	convar* interp;
	convar* interp_ratio;
	convar* min_interp_ratio;
	convar* max_interp_ratio;
	convar* max_unlag;
};

namespace backtrack {
	float get_lerp_time() noexcept;
	bool valid_tick(float simtime, float maxtime) noexcept;
	void update() noexcept;				// Uesd in create_move before prediction
	void run(c_usercmd*) noexcept;		// Uesd in create_move inside preciction
	void frame_stage_notify();			// Uesd in frame_stage_notify

	inline std::deque<player_record> records[65];		// For each player (65) store a deque of records (undefined len)
	inline convars cvars;

	static void init() {
		records->clear();

		cvars.update_rate      = interfaces::console->get_convar("cl_updaterate");
		cvars.max_update_rate  = interfaces::console->get_convar("sv_maxupdaterate");
		cvars.interp           = interfaces::console->get_convar("cl_interp");
		cvars.interp_ratio     = interfaces::console->get_convar("cl_interp_ratio");
		cvars.min_interp_ratio = interfaces::console->get_convar("sv_client_min_interp_ratio");
		cvars.max_interp_ratio = interfaces::console->get_convar("sv_client_max_interp_ratio");
		cvars.max_unlag        = interfaces::console->get_convar("sv_maxunlag");
	}
}