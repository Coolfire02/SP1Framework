#include "MiniGame_WL.h"

MiniGame_WL::MiniGame_WL(LEVEL level, Console& console) : MiniGame(level, console)
{
	ms = 1000;
	water_spawn_delay = 200;
	art.setArt(MINIGAME_WL_ART);
	UPcount = 0;
	DOWNcount = 0;
	isDown = false;
}

MiniGame_WL::~MiniGame_WL() {
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
		setWaterText();
		if ((UPcount >= 4) && (DOWNcount >= 4)) {
			Completed = true;
		}

	}
}

bool MiniGame_WL::processMouseEvents(SMouseEvent&)
{
	return false;
}

void MiniGame_WL::setWaterText()
{
	std::string water = std::to_string(WaterCollected);
	water += water;
	water_ptr->setText(water);
}

std::string MiniGame_WL::getType() {
	return "MiniGame_WL";
}

enum LEVELSTATE MiniGame_WL::getAssociatedLSState() {
	return LS_MINIGAME_WL;
}

void MiniGame_WL::mgGameInit() {
	bucket_ptr = new Bucket;
	water_ptr = new Text;
	wrench_ptr = new Wrench("HEAD");
	wrench_ptr2 = new Wrench("TAIL");
	pipe_ptr = new Pipe;
	mg_obj_ptr.push_back(bucket_ptr);
	mg_obj_ptr.push_back(water_ptr);
	mg_obj_ptr.push_back(wrench_ptr);
	mg_obj_ptr.push_back(pipe_ptr);
	mg_obj_ptr.push_back(wrench_ptr2);
	MiniGameMap.setSize(213, 50);

	//Game initialization
	pipe_ptr->setWorldPosition((MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2) - 72,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);
	bucket_ptr->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2 - 7,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);
	water_ptr->setWorldPosition(0, 1);
	wrench_ptr->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2,
		MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2);// wrench head
	wrench_ptr2->setWorldPosition(MiniGameMap.getMapToBufferOffset().X + g_consoleSize.X / 2 + 2,
		(MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y / 2) - wrench_ptr->getYLength());// wrench tail
	srand(time(NULL));
}

