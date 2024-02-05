#ifndef FR_COMPONENTS_H
#define FR_COMPONENTS_H
#include<fr_genID.h>
namespace FR {

	class moudleID
	{
	public:
		moudleID() = default;
		moudleID(const moudleID&) = default;
		genID ID;
	};

	class moudleName
	{
	public:

		moudleName() = default;
		moudleName(const moudleName&) = default;
		moudleName(const std::string& name): m_Name(name) {}
		std::string m_Name;

	};



}
#endif
