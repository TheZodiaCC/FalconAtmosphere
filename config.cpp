class CfgPatches
{
	class FalconAtmosphere
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts", "DZ_Structures_Residential", "DZ_Structures_Industrial"};
	};
};

class CfgMods
{
	class FalconAtmosphere
	{
	    dir = FalconAtmosphere
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconAtmosphere
	    credits = "";
	    author = "zNitche";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "Mission" };

		class defs
		{
			class imageSets
			{
				files[] = {"FalconAtmosphere\GUI\textures\falcon_imageset.imageset"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconAtmosphere/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconAtmosphere/5_Mission"};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class GeigerCounter: Inventory_Base
	{
		scope = 2;
		displayName = "Geiger counter";
		descriptionShort = "";
		model="FalconAtmosphere\Items\gps\gps.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class AntiRad: Inventory_Base
	{
		scope = 2;
		displayName = "AntiRad";
		descriptionShort = "";
		model = "\dz\gear\medical\Morphine.p3d";
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1.0,{"DZ\gear\medical\data\Morphine.rvmat"}},{0.7,{"DZ\gear\medical\data\Morphine.rvmat"}},{0.5,{"DZ\gear\medical\data\Morphine_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\Morphine_damage.rvmat"}},{0.0,{"DZ\gear\medical\data\Morphine_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Morphine_spear
				{
					soundSet = "Morphine_spear_SoundSet";
					id = 201;
				};
				class Morphine_out
				{
					soundSet = "Morphine_out_SoundSet";
					id = 202;
				};
			};
		};
	};

	class LampLighter: Inventory_Base
	{
		scope = 2;
		displayName = "LL";
		descriptionShort = "";
		model="FalconAtmosphere\Items\gps\gps.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class PoleLight: Inventory_Base
	{
		scope = 2;
		displayName = "Land_Power_Pole_Conc1";
		model = "\dz\vehicles\parts\replacement_headlight.p3d";
		forceFarBubble="true";
		rotationFlags=180;

		class PointLights
		{
				class PointLight
				{
						color[] 	= { 225, 165, 15, 0.5 };
						brightness 	= 0.2;
						radius 		= 15;
						dayLight 	= 0;
						position = "light";
				};
		};
	};

	class PowerGenerator;
	class LightsGenerator: PowerGenerator
	{
		scope = 2;
		displayName = "City Power Generator";
		descriptionShort = "";
		model = "\DZ\gear\camping\power_generator.p3d";
		rotationFlags = 2;
		slopeTolerance = 0.4;
		yawPitchRollLimit[] = {45,45,45};
		weight = 45000;
		itemSize[] = {10,10};
		itemBehaviour = 0;
		attachments[] = {"SparkPlug"};
		fuelTankCapacity = 14000;
		carveNavmesh = 1;
		heavyItem = 1;
		hiddenSelections[] = {"socket_1_plugged","socket_2_plugged","socket_3_plugged","socket_4_plugged","sparkplug_installed","placing"};
		hiddenSelectionsTextures[] = {"dz\gear\camping\data\plug_black_CO.paa","dz\gear\camping\data\plug_yellow_CO.paa","dz\gear\camping\data\plug_white_CO.paa","dz\gear\camping\data\plug_orange_CO.paa","dz\gear\camping\data\power_generator_CO.paa","dz\gear\camping\data\power_generator_CO.paa"};
		hiddenSelectionsMaterials[] = {"dz\gear\camping\data\plug.rvmat","dz\gear\camping\data\plug.rvmat","dz\gear\camping\data\plug.rvmat","dz\gear\camping\data\plug.rvmat","dz\gear\camping\data\power_generator.rvmat","dz\gear\camping\data\power_generator.rvmat"};
		hologramMaterial = "power_generator";
		hologramMaterialPath = "dz\gear\camping\data";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"DZ\gear\camping\data\power_generator.rvmat"}},{0.7,{"DZ\gear\camping\data\power_generator.rvmat"}},{0.5,{"DZ\gear\camping\data\power_generator_damage.rvmat"}},{0.3,{"DZ\gear\camping\data\power_generator_damage.rvmat"}},{0.0,{"DZ\gear\camping\data\power_generator_destruct.rvmat"}}};
				};
			};
		};
		repairableWithKits[] = {7};
		repairCosts[] = {25.0};
		class EnergyManager
		{
			hasIcon = 1;
			autoSwitchOff = 1;
			energyStorageMax = 10000;
			energyUsagePerSecond = 0.28;
			reduceMaxEnergyByDamageCoef = 0.5;
			energyAtSpawn = 5000;
			powerSocketsCount = 4;
			compatiblePlugTypes[] = {2,6};
		};
		class AnimationSources
		{
			class socket_1_plugged
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class socket_2_plugged
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class socket_3_plugged
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class socket_4_plugged
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class sparkplug
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
			class fuel_tank
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
			class sparkplug_installed
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class placing
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
			class dial_fuel
			{
				source = "user";
				animPeriod = 1;
				initPhase = 0;
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class walk
				{
					soundSet = "powergenerator_movement_walk_SoundSet";
					id = 1;
				};
				class pickUpItem_Light
				{
					soundSet = "pickUpPowerGenerator_SoundSet";
					id = 796;
				};
				class pickUpItem
				{
					soundSet = "pickUpPowerGenerator_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "powergenerator_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};


class CfgNonAIVehicles {
	class StaticObject;

	class Static_Lamp_City1: StaticObject {
		scope = 1;
		model = "\DZ\structures\residential\Misc\lamp_city1.p3d";
	};

	class Static_Lamp_City2: StaticObject {
		scope = 1;
		model = "\DZ\structures\residential\Misc\lamp_city2.p3d";
	};

	class Static_Lamp_City3: StaticObject {
		scope = 1;
		model = "\DZ\structures\residential\Misc\lamp_city3.p3d";
	};

	class Static_Lamp_Ind: StaticObject {
		scope = 1;
		model = "\DZ\structures\industrial\Misc\lamp_ind.p3d";
	};

	class Static_Lamp_Rail: StaticObject {
		scope = 1;
		model = "\DZ\structures\industrial\Misc\lamp_rail.p3d";
	};
};

class CfgSoundShaders
{
	class baseCharacter_SoundShader;

	class rad1_Soundshader: baseCharacter_SoundShader
	{
		samples[]=
		{

			{
				"FalconAtmosphere\Sounds\Radiation\rad1",
				0.9
			}
		};
		volume=1;
	};
	class rad2_Soundshader: baseCharacter_SoundShader
	{
		samples[]=
		{

			{
				"FalconAtmosphere\Sounds\Radiation\rad2",
				0.9
			}
		};
		volume=1;
	};
	class rad3_Soundshader: baseCharacter_SoundShader
	{
		samples[]=
		{

			{
				"FalconAtmosphere\Sounds\Radiation\rad3",
				0.9
			}
		};
		volume=1;
	};
};

class CfgSoundSets
{
	class baseCharacter_SoundSet;

	class rad1_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"rad1_SoundShader"
		};
	};
	class rad2_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"rad2_SoundShader"
		};
	};
	class rad3_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"rad3_SoundShader"
		};
	};
};
