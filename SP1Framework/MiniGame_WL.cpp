#include "MiniGame_WL.h"
void MiniGame_WL::setMoneyText() //This is to set the text on the top left to show the player how much money they are losing
{
	std::string money = std::to_string(payreduction);
	money = "Pay Reduction (for wasted water): $" + money;
	Money_ptr->setText(money, 0xC0);
}

MiniGame_WL::MiniGame_WL(LEVEL level, Console& console) : MiniGame(level, console)
{

	MoneyEarned = 0;
	WaterCollected = 0;
	ms = 0;
	water_leak = 10;
	water_spawn_delay = 0;
	water_amt_reduction = 0;
	water_wasted = 0;
	payreduction = 0;
	art.setArt(MINIGAME_WL_ART);
	UPcount = 0;
	DOWNcount = 0;
	isDown = false;
}

MiniGame_WL::~MiniGame_WL() 
{
	//Intentionally left blank.
}

bool MiniGame_WL::processKBEvents(SKeyEvent keyEvents[])
{

	COORD wrenchTail_orig_pos = wrench_ptr2->getWorldPosition();
	COORD  wrenchTail_future_pos = wrenchTail_orig_pos;
	bool eventIsProcessed = false;
	if (keyEvents[K_W].keyDown) {
		wrenchTail_future_pos.Y--;
		eventIsProcessed = true;
		
	}
	if (keyEvents[K_S].keyDown ) {
		wrenchTail_future_pos.Y++;
		eventIsProcessed = true;
		
	}
	if (wrenchTail_future_pos.Y != wrenchTail_orig_pos.Y) {
		wrench_ptr2->setWorldPosition(wrenchTail_future_pos);
		if ((wrench_ptr2->isCollided(*wrench_ptr)) == false) {
			if (wrenchTail_future_pos.Y > bucket_ptr->getWorldPosition().Y) {
				if (isDown != true) {
					isDown = true;
					DOWNcount++;
					water_amt_reduction += 2;
					Beep(30, 30);
				}
			}
			else if (wrenchTail_future_pos.Y < bucket_ptr->getWorldPosition().Y) {
				if (isDown != false) {
					isDown = false;
					UPcount++;
				}
			}
			wrench_ptr2->setWorldPosition(wrenchTail_orig_pos);
		}
	}
	return eventIsProcessed;
}
void MiniGame_WL::gameLoopListener()
{
	if (isStarted()) {
		ms++;
		water_spawn_delay++;
		if (water_spawn_delay == 200)
		{

			water_spawn_delay = 0;
			if ((water_leak - water_amt_reduction) >= 0)
				water_leak = 10 - water_amt_reduction;
			if (WaterCollected >= 30)
			{
				water_wasted += water_leak;
				payreduction = -(water_wasted * getAssociatedLevel());
			}

			else //To ensure water is not reduced over time
				WaterCollected += water_leak;

		}

		double water_filled_percent = (WaterCollected / 30.0)* 100;
		water_ptr->setProgress(water_filled_percent);
		setMoneyText();
		Money_ptr->setRelativePos(0,1);

		if ((UPcount >= 4) && (DOWNcount >= 4)) 
		{
			MoneyEarned = (150 * getAssociatedLevel()) - payreduction;
			Completed = true;
		}

	}
}

bool MiniGame_WL::processMouseEvents(SMouseEvent&)
{
	return false;
}

std::string MiniGame_WL::getType() {
	return "MiniGame_WL";
}

enum LEVELSTATE MiniGame_WL::getAssociatedLSState() {
	return LS_MINIGAME_WL;
}

void MiniGame_WL::mgGameInit() {
	bucket_ptr = new Bucket;
	water_ptr = new ProgressBar(B_VERTICAL, 5, 10);
	wrench_ptr = new Wrench("HEAD");
	wrench_ptr2 = new Wrench("TAIL");
	pipe_ptr = new Pipe;
	Money_ptr = new Text;

	mg_obj_ptr.push_back(Money_ptr);
	mg_obj_ptr.push_back(bucket_ptr);
	mg_obj_ptr.push_back(water_ptr);
	mg_obj_ptr.push_back(wrench_ptr);
	mg_obj_ptr.push_back(pipe_ptr);
	mg_obj_ptr.push_back(wrench_ptr2);
	MiniGameMap.setSize(213, 50);

	//Game initialization

	setMoneyText();

	Money_ptr->setRelativePos(0, 1);
	water_ptr->setRelativePos((MiniGameMap.getXLength() - 15), 10);
	pipe_ptr->setWorldPosition((MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2) - 72,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);
	pipe_ptr->setWorldPosition((MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2) - 72,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);
	bucket_ptr->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2 - 7,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2 - 2);
	wrench_ptr->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);// wrench head
	wrench_ptr2->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2 + 2,
		(MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2) - wrench_ptr->getYLength());// wrench tail
	srand(time(NULL));
}

