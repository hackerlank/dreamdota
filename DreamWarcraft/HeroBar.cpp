#include "stdafx.h"
#include "Offsets.h"
#include "GameStructs.h"
#include "Tools.h"

void *HeroGetButton (war3::CUnit *hero) {
	if (!hero) return NULL;
	war3::CSimpleTop *simpleTop = *(war3::CSimpleTop **)Offset(GLOBAL_SIMPLETOP);
	void *button = NULL;
	if (simpleTop) {
		for (uint32_t i = 0; i < simpleTop->buttonListArrayCount; i++) {
			button = simpleTop->pButtonListArray->pButtonLists[i]->firstButton;
			if (*(void **)button == Offset(HEROBARBUTTON_VTABLE)){
				if (((war3::CHeroBarButton *)button)->hero == hero)
					return button;
			}
		}
	}
	return NULL;
}

bool HeroButtonExists()
{
	war3::CSimpleTop *simpleTop = *(war3::CSimpleTop **)Offset(GLOBAL_SIMPLETOP);
	void *button = NULL;
	if (simpleTop) 
	{
		for (uint32_t i = 0; i < simpleTop->buttonListArrayCount; i++) 
		{
			button = simpleTop->pButtonListArray->pButtonLists[i]->firstButton;
			if (*(void **)button == Offset(HEROBARBUTTON_VTABLE))
			{
				return true;
			}
		}
	}
	return false;
}