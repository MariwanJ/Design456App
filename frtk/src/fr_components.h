#ifndef FR_COMPONENTS_H
#define FR_COMPONENTS_H
#include<fr_genID.h>
namespace FR {

	class FRTK_API ItemID
	{
	public:
		ItemID() = default;
		ItemID(const ItemID&) = default;
		genID ID;
	};

	class FRTK_API ItemName
	{
	public:

		ItemName() = default;
		ItemName(const ItemName&) = default;
		ItemName(const std::string& name): m_Name(name) {}
		std::string m_Name;

	};

}
#endif
