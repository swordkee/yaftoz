/**
 * Yaf Config Abstract
 */
/**
 * @namespace
 */
namespace Yaf;

abstract class Config_Abstract
{
    /**
     * holds the config array
     * @var array
     */
    protected _config = [];
    /**
     * Whether the config is  readonly and cannot be changed/modified
     * true means canmot be changed
     * false means can be changed
     * @var boolean
     */
    protected _readonly = false;
    public abstract function get(name) -> void;
    
    public abstract function set(name, value) -> void;
    
    public function readonly()
    {
        
        return this->_readonly;
    }
    
    public abstract function toArray() -> void;

}