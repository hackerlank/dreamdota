#ifndef DAMAGEDISPLAY_H_
#define DAMAGEDISPLAY_H_

namespace DamageDisplay {

	void Init ( );
	void Cleanup( );

	void DisableUnit(Unit* u);
	void EnableUnit(Unit* u);
}
#endif
