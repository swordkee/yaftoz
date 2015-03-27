/**
 * @todo check an example to see how does it work
 * Yaf Action Abstract
 */
/**
 * @namespace
 */
namespace Yaf;

abstract class Action_Abstract extends \Yaf\Controller_Abstract
{
    protected _controller = null;
    public function execute() -> void
    {
    }
    public function setController(<Controller_Abstract> controller) -> void
    {
        let this->_controller = controller;
    }

    public function getController()
    {
        return this->_controller;
    }
}