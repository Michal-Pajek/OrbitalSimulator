#include "body/summary/BodySummary.hpp"

#include "body/Body.hpp"
#include "body/types/BodyTypeCatalog.hpp"

#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace body::summary
{
	void print(const Body& body, const bool oneLine)
	{
		const auto sep{ oneLine ? '\t' : '\n' };
		ui::console::writeLine(
			body.getName(), " (", BodyTypeCatalog::getType(body.getTypeId()).getTextId(), ')', sep,
			localization::TextId::Mass, " (kg): ", body.getMass(), sep,
			localization::TextId::Position, " (m): ", body.getPosition(), sep,
			localization::TextId::Velocity, " (m/s): ", body.getVelocity());
	}
} // namespace body::summary
