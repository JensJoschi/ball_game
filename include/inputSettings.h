#pragma once

/** @cond */
#include <sfml/Graphics.hpp>
#include <cassert>
/** @endcond */

struct ControllerSettings {
	double sensitivity{ 0.0 }; /**< Describes how much an object is moved by 1 action call. */
};


struct InputSettings {
	explicit InputSettings(double sensitivity) :general(sensitivity) {}
	virtual ~InputSettings() = default;
	InputSettings(const InputSettings&) = delete;
	InputSettings& operator=(const InputSettings&) = delete;
	InputSettings(InputSettings&&) noexcept = default;
	InputSettings& operator=(InputSettings&&) noexcept = default;

	virtual int getType() const = 0;
protected:
	ControllerSettings general;
};

struct PlayerMouseParams : public InputSettings {
	PlayerMouseParams(double sensitivity, const sf::RenderWindow& win) : InputSettings(sensitivity), m_win(win) {
		assert(m_win.isOpen());
	}
	~PlayerMouseParams() override = default;
	PlayerMouseParams(PlayerMouseParams&&) noexcept = default;
	PlayerMouseParams& operator=(PlayerMouseParams&&) noexcept = default;

	int getType() const override { return 0; }
private:
	const sf::Window& m_win;
};

struct PlayerKBSetupParams : public InputSettings {
	PlayerKBSetupParams(double sensitivity, sf::Keyboard::Key up, sf::Keyboard::Key down) : InputSettings(sensitivity), m_upKey(up), m_downKey(down) {
		assert(m_upKey != m_downKey);
	}
	~PlayerKBSetupParams() override = default;
	PlayerKBSetupParams(PlayerKBSetupParams&&) noexcept = default;
	PlayerKBSetupParams& operator=(PlayerKBSetupParams&&) noexcept = default;

	int getType() const override { return 1; }
private:
	sf::Keyboard::Key m_upKey;
	sf::Keyboard::Key m_downKey;
};

struct AISetupParams : public InputSettings {
	AISetupParams(double sensitivity, bool left) : InputSettings(sensitivity), m_own(left ? items::P1 : items::P2) {
	}
	~AISetupParams() override = default;
	AISetupParams(AISetupParams&&) noexcept = default;
	AISetupParams& operator=(AISetupParams&&) noexcept = default;
	int getType() const override { return 2; }
private: 
	items m_own;
};