// ================================================================================
// == This file is a part of Tinkerbell UI Toolkit. (C) 2011-2012, Emil Seger�s ==
// ==                   See tinkerbell.h for more information.                   ==
// ================================================================================

#ifndef TB_ADDON_H
#define TB_ADDON_H

#include "tb_linklist.h"
#include "tb_widgets.h"

namespace tinkerbell {

/** TBAddon provides a simple API with Init/Shutdown callbacks that will
	be called during init_tinkerbell and shutdown_tinkerbell. */

class TBAddon : public TBLinkOf<TBAddon>
{
public:
	/** Called during init_tinkerbell after tinkerbell core has been initiated. */
	virtual bool Init() = 0;

	/** Called during shutdown_tinkerbell before tinkerbell core has been shut down. */
	virtual void Shutdown() = 0;

	virtual ~TBAddon() {}
};

/** TBAddonFactory is ment to be subclassed to create a TBAddon, by
	being declared as a global object. It will then register itself
	so the addon is created, initiated during init_tinkerbell and
	destroyed during shutdown_tinkerbell. */
class TBAddonFactory
{
public:
	TBAddonFactory();

	virtual TBAddon *CreateAddon() = 0;

	TBAddonFactory *next;	///< Next registered addon factory.
};

/** Init addons. */
bool TBInitAddons();

/** Shutdown and delete addons. */
void TBShutdownAddons();

}; // namespace tinkerbell

#endif // TB_ADDON_H