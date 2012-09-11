/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <TagGroups/Halo1/TagGroupDefinitions.hpp>
#include <TagGroups/Halo1/object_definitions.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_number_of_magazines_per_weapon = 2,
		};

		enum grenade_type : _enum
		{
			_grenade_type_frag,
			_grenade_type_plasma,

			_grenade_type
		};

		enum equipment_powerup : _enum
		{
			_equipment_powerup_none,

			_equipment_powerup_double_shield,
			_equipment_powerup_over_shield,
			_equipment_powerup_active_camo,
			_equipment_powerup_full_spectrum_vision,

			_equipment_powerup_health,
			_equipment_powerup_grenade,

			_equipment_powerup
		};

		enum equipment_yelo_type : _enum
		{
			_equipment_yelo_type_none,

			_equipment_yelo_type_armor_ability,
			_equipment_yelo_type_deployable,

			_equipment_yelo_type,
		};

		enum equipment_yelo_function_mode : _enum
		{
			_equipment_yelo_function_mode_none,

			_equipment_yelo_function_mode,
		};
	};

	namespace Flags
	{
		enum equipment_yelo_flags : word_flags
		{
		};
	};

	namespace TagGroups
	{
		struct _item_definition
		{
			struct _item_definition_flags {
				TAG_FLAG(maintains_z_up);
				TAG_FLAG(destroyed_by_explosions);
				TAG_FLAG(unaffected_by_gravity);
			}flags; BOOST_STATIC_ASSERT( sizeof(_item_definition_flags) == sizeof(long_flags) );

			int16 message_index;
			int16 sort_order;
			real scale;
			int16 hud_message_value_scale;
			PAD16;

			TAG_PAD(int32, 4);
			_enum function_exports[4];
			TAG_PAD(int32, 41);

			struct {
				TAG_FIELD(tag_reference, material_effects, "foot");
				TAG_FIELD(tag_reference, collision_sound, "snd!");
			}references;

			TAG_PAD(int32, 30);

			struct {
				real_bounds delay;
				TAG_FIELD(tag_reference, detonating_effect, "effe");
				TAG_FIELD(tag_reference, effect, "effe");
			}detonation;
		}; BOOST_STATIC_ASSERT( sizeof(_item_definition) == 0x18C );


		struct s_item_definition : s_object_definition
		{
			_item_definition item;
		};


		//////////////////////////////////////////////////////////////////////////
		// equipment

		struct s_equipment_yelo_armor_ability
		{
			struct s_tank {
				TAG_FIELD(real, size);
				TAG_FIELD(real, recharge_rate);
				TAG_FIELD(int16, count);
				TAG_FIELD(int16, swap_time);
			}fuel_tank;

			struct s_fuel {
				TAG_FIELD(real, cost);
				TAG_FIELD(real, recharge_rate);
				TAG_FIELD(real, recharge_cooldown);
			}fuel;
		};
		struct s_equipment_yelo_deployable
		{
			TAG_FIELD(int16, usage_count);
			PAD16;
		};

		struct s_equipment_yelo_definition
		{
			enum { k_max_definition_size = sizeof(tag_reference)*9 }; // size of the useless padding in equipment

			TAG_FIELD(Flags::equipment_yelo_flags, flags);
			PAD16;
			PAD32; PAD32; PAD32;

			struct s_effects {
				TAG_FIELD(tag_reference, activate, 'effe', 'snd!');
				TAG_FIELD(tag_reference, active, 'effe', 'snd!');
				TAG_FIELD(tag_reference, deactivate, 'effe', 'snd!');
			}effects;

		}; BOOST_STATIC_ASSERT( sizeof(s_equipment_yelo_definition) <= s_equipment_yelo_definition::k_max_definition_size );
		struct _equipment_definition
		{
			TAG_ENUM(powerup_type, Enums::equipment_powerup);
			TAG_ENUM(grenade_type, Enums::grenade_type);
			TAG_FIELD(real, powerup_time);
			TAG_FIELD(tag_reference, pickup_sound, 'snd!');
			union {
				TAG_PAD(byte, s_equipment_yelo_definition::k_max_definition_size);
				//s_equipment_yelo_definition yelo;
			};
		}; BOOST_STATIC_ASSERT( sizeof(_equipment_definition) == 0xA8 );
		struct s_equipment_definition : s_item_definition
		{
			enum { k_group_tag = 'eqip' };

			_equipment_definition equipment;
		};


		//////////////////////////////////////////////////////////////////////////
		// weapon

		struct aim_assist_parameters
		{
			TAG_FIELD(angle, autoaim_angle);
			TAG_FIELD(real, autoaim_range);
			TAG_FIELD(angle, magnetism_angle);
			TAG_FIELD(real, magnetism_range);
			TAG_FIELD(angle, deviation_angle);
			PAD32;
		};
		struct weapon_ammunition_object
		{
			TAG_FIELD(int16, rounds);
			PAD16; PAD64;
			TAG_FIELD(tag_reference, equipment);
		}; BOOST_STATIC_ASSERT( sizeof(weapon_ammunition_object) == 0x1C);
		struct weapon_magazine_definition
		{
			struct _flags {
				TAG_FLAG(wastes_rounds_when_reloaded);
				TAG_FLAG(every_round_must_be_chambered);
			}flags; BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(long_flags) );
			TAG_FIELD(int16, rounds_recharged);
			TAG_FIELD(int16, rounds_total_initial);
			TAG_FIELD(int16, rounds_total_maximum);
			TAG_FIELD(int16, rounds_loaded_maximum);
			TAG_PAD(int32, 2);
			TAG_FIELD(real, reload_time);
			TAG_FIELD(int16, rounds_reloaded);
			PAD16;
			TAG_FIELD(real, chamber_time);
			TAG_PAD(int32, 2);
			TAG_PAD(tag_reference, 1);
			TAG_FIELD(tag_reference, reloading_effect);
			TAG_FIELD(tag_reference, chambering_effect);
			TAG_PAD(tag_block, 1);
			TAG_TBLOCK(magazines, weapon_ammunition_object);
		}; BOOST_STATIC_ASSERT( sizeof(weapon_magazine_definition) == 0x70);
		struct weapon_trigger_firing_effect
		{
			TAG_FIELD(short_bounds, shot_count);
			TAG_PAD(tag_string, 1);
			TAG_FIELD(tag_reference, firing_effect);
			TAG_FIELD(tag_reference, misfire_effect);
			TAG_FIELD(tag_reference, empty_effect);
			TAG_FIELD(tag_reference, firing_damage);
			TAG_FIELD(tag_reference, misfire_damage);
			TAG_FIELD(tag_reference, empty_damage);
		}; BOOST_STATIC_ASSERT( sizeof(weapon_trigger_firing_effect) == 0x84);
		struct weapon_trigger_definition
		{
			struct _flags{
				TAG_FLAG(tracks_fired_projectile);
				TAG_FLAG(random_firing_effects);
				TAG_FLAG(can_fire_with_partial_ammo);
				TAG_FLAG(does_not_repeat_automatically);
				TAG_FLAG(locks_in_on_off_state);
				TAG_FLAG(projectiles_use_weapon_origin);
				TAG_FLAG(sticks_when_dropped);
				TAG_FLAG(ejects_during_chamber);
				TAG_FLAG(discharging_spews);
				TAG_FLAG(analog_rate_of_fire);
				TAG_FLAG(use_error_when_unzoomed);
				TAG_FLAG(projectile_vector_cannot_be_adjusted);
				TAG_FLAG(projectiles_have_identical_error);
				TAG_FLAG(projectile_is_client_side_only);
			}flags; BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(long_flags) );

			//firing
			TAG_FIELD(real_bounds, rounds_per_second);
			TAG_FIELD(real, firing_acceleration_time);
			TAG_FIELD(real, firing_deceleration_time);
			TAG_FIELD(real_fraction, blurred_rate_of_fire);
			TAG_PAD(int32, 2);
			TAG_FIELD(int16, magazine);
			TAG_FIELD(int16, rounds_per_shot);
			TAG_FIELD(int16, minimum_rounds_loaded);
			TAG_FIELD(int16, rounds_between_tracers);
			PAD32;
			PAD16;
			TAG_ENUM(firing_noise);

			//error
			TAG_FIELD(real_bounds, error);
			TAG_FIELD(real, error_acceleration_time);
			TAG_FIELD(real, error_deceleration_time);
			TAG_PAD(int32, 2);

			//charging
			TAG_FIELD(real, charging_time);
			TAG_FIELD(real, charged_time);
			TAG_ENUM(overcharged_action);
			PAD16;
			TAG_FIELD(real, charged_illumination);
			TAG_FIELD(real, spew_time);
			TAG_FIELD(tag_reference, charging_effect);

			//projectile
			TAG_ENUM(distribution_function);
			TAG_FIELD(int16, projectiles_per_shot);
			TAG_FIELD(real, distribution_angle);
			PAD32;
			TAG_FIELD(angle, minimum_error);
			TAG_FIELD(angle_bounds, error_angle);
			TAG_FIELD(real_point3d, first_person_offset);
			PAD32;
			TAG_FIELD(tag_reference, projectile);

			//misc
			TAG_FIELD(real, ejection_port_recovery_time);
			TAG_FIELD(real, illumination_recovery_time);
			TAG_PAD(int32, 3);
			TAG_FIELD(real_fraction, heat_generated_per_round);
			TAG_FIELD(real_fraction, age_generated_per_round);
			TAG_FIELD(real_fraction, age_generated_while_charged);
			TAG_FIELD(real, overload_time);
			TAG_PAD(int32, 2);
			TAG_PAD(tag_string, 1);
			struct { // all times are in game ticks (source fields are in seconds)
				real illumination_recovery_time;
				real ejection_port_recovery_time;
				real firing_acceleration_time;
				real firing_deceleration_time;
				real error_acceleration_time;
				real error_deceleration_time;
			}postprocessed;
			TAG_TBLOCK(firing_effects, weapon_trigger_firing_effect);
		}; BOOST_STATIC_ASSERT( sizeof(weapon_trigger_definition) == 0x114);
		struct _weapon_definition
		{
			struct _flags {
				TAG_FLAG(vertical_heat_display);
				TAG_FLAG(mutually_exclusive_triggers);
				TAG_FLAG(attacks_automatically_on_bump);
				TAG_FLAG(must_be_readied);
				TAG_FLAG(doesnt_count_toward_maximum);
				TAG_FLAG(aim_assists_only_when_zoomed);
				TAG_FLAG(prevents_grenade_throwing);
				TAG_FLAG(must_be_picked_up);
				TAG_FLAG(holds_triggers_when_dropped);
				TAG_FLAG(prevents_melee_attack);
				TAG_FLAG(detonates_when_dropped);
				TAG_FLAG(cannot_fire_at_maximum_age);
				TAG_FLAG(secondary_trigger_overrides_grenades);
				TAG_FLAG(OBSOLETEdoes_not_depower_active_camo_in_multilplayer);
				TAG_FLAG(enables_integrated_night_vision);
				TAG_FLAG(AIs_use_weapon_melee_damage);
				TAG_FLAG(third_person_weapon);
			}flags; BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(long_flags) );
			TAG_FIELD(tag_string, label);
			TAG_ENUM(secondary_trigger_mode);
			TAG_FIELD(int16, maximum_alternate_shots_loaded);

			//export to functions
			TAG_ENUM(A_in);
			TAG_ENUM(B_in);
			TAG_ENUM(C_in);
			TAG_ENUM(D_in);
			TAG_FIELD(real, ready_time);
			TAG_FIELD(tag_reference, ready_effect);

			//heat
			TAG_FIELD(real_fraction, heat_recovery_threshold);
			TAG_FIELD(real_fraction, overheated_threshold);
			TAG_FIELD(real_fraction, heat_detonation_threshold);
			TAG_FIELD(real_fraction, heat_detonation_fraction);
			TAG_FIELD(real_fraction, heat_loss_per_second);
			TAG_FIELD(real_fraction, heat_illumination);
			TAG_PAD(int32, 4);
			TAG_FIELD(tag_reference, overheated);
			TAG_FIELD(tag_reference, detonation);
			TAG_FIELD(tag_reference, player_melee_damage);
			TAG_FIELD(tag_reference, player_melee_response);
			TAG_PAD(int32, 2);

			//actor firing parameters
			TAG_FIELD(tag_reference, actor_firing_parameters);

			//reticle
			TAG_FIELD(real, near_reticle_range);
			TAG_FIELD(real, far_reticle_range);
			TAG_FIELD(real, intersection_reticle_range);

			//zoom
			PAD16;
			TAG_FIELD(int16, magnification_levels);
			TAG_FIELD(real_bounds, magnification_range);

			aim_assist_parameters aim_assist;

			//movement
			TAG_ENUM(movement_penalized);
			PAD16;
			TAG_FIELD(real_fraction, forward_movement_penalty);
			TAG_FIELD(real_fraction, sideways_movement_penalty);
			PAD32;

			//AI targeting parameters
			TAG_FIELD(real, minimum_target_range);
			TAG_FIELD(real, looking_time_modifier);
			PAD32;

			//miscellaneous
			TAG_FIELD(real, light_power_on_time);
			TAG_FIELD(real, light_power_off_time);
			TAG_FIELD(tag_reference, light_power_on_effect);
			TAG_FIELD(tag_reference, light_power_off_effect);
			TAG_FIELD(real, age_heat_recovery_penalty);
			TAG_FIELD(real, age_rate_of_fire_penalty);
			TAG_FIELD(real_fraction, age_misfire_start);
			TAG_FIELD(real_fraction, age_misfire_chance);
			TAG_PAD(int32, 3);

			//interface
			TAG_FIELD(tag_reference, first_person_model);
			TAG_FIELD(tag_reference, first_person_animations);
			PAD32;
			TAG_FIELD(tag_reference, hud_interface);
			TAG_FIELD(tag_reference, pickup_sound);
			TAG_FIELD(tag_reference, zoom_in_sound);
			TAG_FIELD(tag_reference, zoom_out_sound);
			TAG_PAD(tag_block, 1);
			TAG_FIELD(real, active_camo_ding);
			TAG_FIELD(real, active_camo_regrowth_rate);
			TAG_PAD(int32, 3);

			//more miscellaneous
			PAD16;
			TAG_ENUM(weapon_type);
			TAG_TBLOCK(predicted_resources, predicted_resource);
			TAG_TBLOCK(magazines, weapon_magazine_definition);
			TAG_TBLOCK(triggers, weapon_trigger_definition);
		}; BOOST_STATIC_ASSERT( sizeof(_weapon_definition) == 0x200);

		struct s_weapon_definition : s_item_definition
		{
			enum { k_group_tag = 'weap' };

			_weapon_definition weapon;
		};
	};
};