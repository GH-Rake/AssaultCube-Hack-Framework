#include "aimbot.h"

void FW::ShootThread(FW::Aimbot_t * aimbot, bool *bAimbot)
{
	INPUT leftMouseShoot = { 0 };
	while (1)
	{
		if (aimbot->target && bAimbot && GetAsyncKeyState(VK_RBUTTON))
		{
			//press
			leftMouseShoot.type = INPUT_MOUSE;
			leftMouseShoot.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &leftMouseShoot, sizeof(INPUT));

			std::this_thread::sleep_for(std::chrono::milliseconds(5));

			// Release
			leftMouseShoot.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &leftMouseShoot, sizeof(INPUT));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

bool FW::SortByAngle(FW::Player_t *lhs, FW::Player_t *rhs)
{
	//if (abs(lhs->angleDiff - rhs->angleDiff) < 30)
	{
		//return lhs->dist < rhs->dist;
	}
	//else
	return lhs->angleDiff < rhs->angleDiff;
}

void FW::Aimbot_t::StartShootThread(bool * bAimbot)
{
	std::thread shootThread(ShootThread, this, bAimbot);
	shootThread.detach();
}

void FW::Aimbot_t::GetCrossHair(int viewport[4])
{
	crossHair.x = viewport[2] / 2;
	crossHair.y = viewport[3] / 2;
}

void FW::Aimbot_t::MoveMouse(vec3 target, int windowWidth, int windowHeight)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = target.x - windowWidth / 2;
	Input.mi.dy = target.y - windowHeight / 2;
	SendInput(1, &Input, sizeof(INPUT));
}

//wtf localPlayer in here?
void FW::Aimbot_t::GetTarget(Player_t localPlayer)
{
	//if target is locked, don't get new target
	if (target && bTargetLock)
	{
		//if still a valid target
		if (target->IsValid()) //shit is not getting updated in this loop, gonna need a pointer...fuck
		//if (target->bValid) ///////////////////////////////
		{
			return;
		}
		else bTargetLock = false;
	}

	targets.clear();
	target = nullptr;

	for (auto &p : FW::Aimbot_t::players)
	{
		if (!p.bEnemy) continue;
		if (!p.bVisible) continue;

		if (!p.IsVisible(localPlayer)) continue; //visibility check calling base function not overridden

		targets.push_back(&p);
	}

	sort(targets.begin(), targets.end(), SortByAngle);

	if (!targets.empty())
	{
		target = targets[0];
		bTargetLock = true;
	}
}