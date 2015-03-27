/**
 * Yaf_Response_Cli
 *
 * CLI response for controllers
 *
 */
/**
 * @namespace
 */
namespace Yaf\Response;
use Yaf\Response_Abstract;
class Cli extends Response_Abstract
{
    /**
     * Magic __toString functionality
     *
     * @return string
     */
    public function __toString() -> string
    {
        
        return this->_body;
    }

}