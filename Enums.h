#pragma once

	enum Direction { North, East, South, West };

	enum MoveResultAction
	{
		Undefined = -1,
		Blocked = 0,
		MoveOk = 1,
		Fight = 2,
		LoadNewRoom = 3
	};


