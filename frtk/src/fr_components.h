#ifndef FR_COMPONENTS_H
#define FR_COMPONENTS_H
#include<fr_genID.h>
namespace FR {

	class FRTK_API moudleID
	{
	public:
		moudleID() = default;
		moudleID(const moudleID&) = default;
		genID ID;
	};

	class FRTK_API moudleName
	{
	public:

		moudleName() = default;
		moudleName(const moudleName&) = default;
		moudleName(const std::string& name): m_Name(name) {}
		std::string m_Name;

	};

}
#endif
