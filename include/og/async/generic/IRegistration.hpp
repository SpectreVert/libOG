/*
 * Created by Costa Bushnaq
 *
 * 29-03-2021 @ 20:29:41
 *
 * see LICENSE
*/

#ifndef _FIXME
#define _FIXME

#include "og/core/Tag.hpp"

namespace og {

namespace net {

class IBadge {
public:

	virtual ~IBadge();

	core::Tag id() const = 0;

}; // class IBadge

} // namespace net

} // namespace og

#endif /* _FIXME */

