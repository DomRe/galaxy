///
/// StateMachine.hpp
/// galaxy
///
/// Created by reworks on 18/05/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_STATEMACHINE_HPP_
#define GALAXY_STATEMACHINE_HPP_

#include <stack>
#include <utility>
#include <unordered_map>

#include "galaxy/types/State.hpp"
#include "galaxy/libs/loguru/loguru.hpp"
#include "galaxy/libs/cereal/types/stack.hpp"

namespace galaxy
{
	///
	/// A state stack for the gamestates.
	/// A seperate one would probably be needed for a character state system.
	/// This was designed to be used purely for gamestates.
	///
	class StateMachine
	{
		friend class cereal::access;
	public:
		///
		/// Constructor.
		///
		StateMachine() = default;

		///
		/// Destructor.
		///
		~StateMachine() noexcept = default;
	    
		///
		/// Load the current state resources.
		///
		void load();

		///
		/// Unloads the current state resources.
		///
		void unload();

        ///
		/// Poll for events in the current state.
		///
		void event(ALLEGRO_EVENT* event);
        
		///
		/// Updates the current state.
		///
		/// \param dt Delta Time from game loop.
		///
		void update(const double dt);

		///
		/// Render the current state.
		///
		void render();

		///
		/// \brief Create a new state to the machine.
		///
		/// Template Typename State is the type of the state to add and 
		/// the args are the arguments to construct that state.
		///
		/// \param id Name of the state to identify it by.
		/// \param args Arguments to construct the state.
		///
		/// \return Returns pointer to newly created state.
		///
		template<typename State, typename ... Args>
		State* createState(const std::string& id, Args&&... args);

		///
		/// Push a new state to the top of the stack.
		///
		/// \param state State ID to push.
		///
		void push(const std::string& state);

		///
		/// Pop the top state.
		///
		void pop();

		///
		/// \brief The current top state.
		///
		/// \return Returns StateType* pointer or just a State* by default.
		///
		template<typename S = State>
		S* top();

	private:
		///
		/// Cereal serialize function.
		///
		template<class Archive>
		inline void serialize(Archive& ar)
		{
			ar(m_stack);
		}

	private:
		///
		/// The stack for manipulation.
		/// Operates off of std::string because that allows us to serialize the current game state simply,
		/// rather than dealing with complex pointer serialization or having to have annoying enums for integer based
		/// IDs.
		/// You also can't use the type because the type signature could change depending on the system implementation.
		///
		std::stack<std::string> m_stack;

		///
		/// Stores the states.
		///
		std::unordered_map<std::string, std::unique_ptr<State>> m_states;
	};

	template<typename State, typename ... Args>
	inline State* StateMachine::createState(const std::string& id, Args&&... args)
	{
		// Construct in place by forwarding arguments to the object.
		m_states.emplace(id, std::make_unique<State>(std::forward<Args>(args)...));

		return dynamic_cast<State*>(m_states[id].get());
	}

	template<typename S>
	inline S* StateMachine::top()
	{
		S* output = nullptr;

		// Ensure there are valid states and a non-empty stack
		if (!m_stack.empty() && !m_states.empty())
		{
			output = m_states[m_stack.top()].get();
		}
		else
		{
			LOG_S(FATAL) << "Attempted to access a state while no states exist or stack is empty." << " Stack size: " << m_stack.size() << ". State map size: " << m_states.size() << ".";
		}

		return output;
	}
}

#endif