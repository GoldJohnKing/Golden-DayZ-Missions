#include "$CurrentDir:mpmissions/dayzOffline.chernarusplus/eAI/AI_init.c" // Edited: Add eAI support

void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
	
	InitDynamicPatrols(); // Edited: Add eAI support
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		// Edited: Remove all player items
		player.RemoveAllItems();

		// Edited: Get player's reference
		itemClothing = player;

		// itemClothing = player.FindAttachmentBySlotName( "Body" ); // Edited: No need to place items only in clothes
		if ( itemClothing )
		{
			// Edited: Add clothes to player
			string clothesArray[] = { "Blouse_Blue","Blouse_Green","Blouse_Violet","Blouse_White","PrisonUniformJacket","Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_PlaneBlack","Shirt_RedCheck","Shirt_WhiteCheck" };
			int rndIndex = Math.RandomInt( 0, 11 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( clothesArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add pants to player
			string pantsArray[] = { "CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey","CanvasPants_Red","CanvasPants_Violet","Breeches_Beetcheck","Breeches_Beige","Breeches_Black","Breeches_Blackcheck","Breeches_Blue","Breeches_Browncheck","Breeches_Green","Breeches_Pink","Breeches_Red","Breeches_White" };
			rndIndex = Math.RandomInt( 0, 15 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( pantsArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add backpack to player
			string backpackArray[] = { "ChildBag_Blue","ChildBag_Green","ChildBag_Red","CourierBag","FurCourierBag" };
			rndIndex = Math.RandomInt( 0, 5 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( backpackArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add shoes to player
			string shoesArray[] = { "HikingBootsLow_Beige","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Grey" };
			rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( shoesArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// SetRandomHealth( itemClothing ); // Edited: We've already done it before
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 4 ); // Edited: Increase bandage quantity, default = 2

			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			rndIndex = Math.RandomInt( 0, 4 ); // Edited: Avoid duplicated defination, default = int rndIndex
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// rand = Math.RandomFloatInclusive( 0.0, 1.0 ); // Edited: Disable default random food spawn
			// if ( rand < 0.35 )
			// 	itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			// else if ( rand > 0.65 )
			// 	itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			// else
			// 	itemEnt = player.GetInventory().CreateInInventory( "Plum" );

			// SetRandomHealth( itemEnt );

			// Edited: Add basic food to player
			string basicFoodsArray[] = { "Apple","Pear","Plum","Tomato","GreenBellPepper","Potato","SlicedPumpkin" };
			rndIndex = Math.RandomInt( 0, 7 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( basicFoodsArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add solid food to player
			string solidFoodsArray[] = { "Chips","Crackers","Rice","SaltySticks" };
			rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( solidFoodsArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add drink to player
			string drinkArray[] = { "SodaCan_Cola","SodaCan_Kvass","SodaCan_Pipsi","SodaCan_Spite" };
			rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( drinkArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add knife to player
			string knivesArray[] = { "SteakKnife","HuntingKnife","KitchenKnife" };
			rndIndex = Math.RandomInt( 0, 3 );
			itemEnt = player.GetInventory().CreateInInventory( knivesArray[rndIndex] );
			SetRandomHealth( itemEnt );

			// Edited: Add tent to player
			string tentsArray[] = { "MediumTent","MediumTent_Green","MediumTent_Orange" };
			rndIndex = Math.RandomInt( 0, 3 );
			itemEnt = player.GetInventory().CreateInInventory( tentsArray[rndIndex] );
			SetRandomHealth( itemEnt );
		}
		
		// itemClothing = player.FindAttachmentBySlotName( "Legs" ); // Edited: We've already done it before
		// if ( itemClothing )
		// 	SetRandomHealth( itemClothing );
		
		// itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}