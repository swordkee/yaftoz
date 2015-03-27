/**
 * Yaf_Request_Simple
 *
 */
/**
 * @namespace
 */
namespace Yaf\Request;
use Yaf\Response_Abstract;
use Yaf\Request_Abstract;
class Simple extends \Yaf\Request_Abstract
{
    public function __construct(method = null,  module = null, controller = null, action = null, params = []) -> void
    {
        var sapiType;

        if !is_array(params) {
            throw new \Yaf\Exception\TypeError("Expects the params is an array");
        }

        if method == null {
            if fetch method, _SERVER["REQUEST_METHOD"] {
                let this->method = method;
            } else {
                let sapiType =  php_sapi_name();

                if strtolower(sapiType) == "cli" || substr(sapiType, 0, 3) == "cgi" {
                    let method = "CLI";
                } else {
                    let method = "unknown";
                }
            }
        }
        //let this->method = method;
        
        if module != null || action != null || controller != null {
            this->setActionName(action);
            this->setControllerName(controller);
            this->setModuleName(module);
            this->setRouted(true);
        } else {
            
            if module == null {
                this->setModuleName(\Yaf\G::get("default_module"));
            }
            
            if controller == null {
                this->setControllerName(\Yaf\G::get("default_controller"));
            }
            
            if action == null {
                this->setActionName(\Yaf\G::get("default_action"));
            }
        }
        
        if params {
            this->setParam(params);
        }
    }
    
    protected function __clone() -> void
    {
    }

}