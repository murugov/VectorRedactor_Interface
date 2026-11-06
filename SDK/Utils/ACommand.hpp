#ifndef A_COMMAND_HPP
#define A_COMMAND_HPP

namespace Vectoria {

class ACommand
{
public:
    virtual ~ACommand() = default;

    virtual void execute() const = 0;
};

} // namespace Vectoria

#endif