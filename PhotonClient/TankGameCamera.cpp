#include "TankGameCamera.h"
#include "InputManager.h"

void Photon::TankGameCamera::SetFollowTarget(Entity* target)
{
	m_follow_target = target;
}

void Photon::TankGameCamera::SetFollowTargetOffset(glm::vec3 offset)
{
	m_follow_target_offset = offset;
}

void Photon::TankGameCamera::HandleInput(float delta_time)
{
	InputManager input_manager_instance = InputManager::Instance();
	if (input_manager_instance.GetKey(KeyCode::W, KeyAction::Pressed))
	{
		m_position += m_current_speed * m_rotation;
	}
	if (input_manager_instance.GetKey(KeyCode::S, KeyAction::Pressed))
	{
		m_position += m_current_speed * -m_rotation;
	}
	if (input_manager_instance.GetKey(KeyCode::A, KeyAction::Pressed))
	{
		m_position += m_current_speed * -glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (input_manager_instance.GetKey(KeyCode::D, KeyAction::Pressed))
	{
		m_position += m_current_speed * glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (input_manager_instance.GetMouseButton(MouseKey::LeftMouseButton, KeyAction::Pressed))
	{
		input_manager_instance.SetCursorVisibility(false);
		if (m_first_clicked)
		{
			input_manager_instance.SetMousePosition((m_width / 2), (m_height / 2));
			m_first_clicked = false;
		}

		glm::vec2 mouse_pos = input_manager_instance.GetMousePosition();

		float rot_x = m_sensitivity * (float)(mouse_pos.y - (m_height / 2)) / m_height;
		float rot_y = m_sensitivity * (float)(mouse_pos.x - (m_width / 2)) / m_width;

		glm::vec3 new_rotation =
			glm::rotate(m_rotation, glm::radians(-rot_x), glm::normalize(glm::cross(m_rotation, m_up)));

		if (abs(glm::angle(new_rotation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_rotation = new_rotation;
		}

		m_rotation = glm::rotate(m_rotation, glm::radians(-rot_y), m_up);

		input_manager_instance.SetMousePosition((m_width / 2), (m_height / 2));
	}
	else if (input_manager_instance.GetMouseButton(MouseKey::LeftMouseButton, KeyAction::Release))
	{
		input_manager_instance.SetCursorVisibility(true);
		m_first_clicked = true;
	}
}
