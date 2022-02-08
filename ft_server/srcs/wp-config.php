<?php
define( 'DB_NAME', 'wordpress' );
define( 'DB_USER', 'vspinell' );
define( 'DB_PASSWORD', 'ciao' );
define( 'DB_HOST', 'localhost' );
define( 'DB_CHARSET', 'utf8' );
define( 'DB_COLLATE', '' );

define('AUTH_KEY',         '8*8]9Y1FL$aqPd<.XTeW!xpQI;ZStf[VKnYMt{0os.-Gh^kb_4$=e_/O!DCp0&C ');
define('SECURE_AUTH_KEY',  'RG:(3=J|FT`#Pu+2_C#1Xr397jx/6^Ig/4I(/K>g]h{$|aiSR.pI:6pt|FC|/&q+');
define('LOGGED_IN_KEY',    'qdI@d;s_`_R94kwEg(S*,pW4CY|k]F0+gZ|?y3K|-zOUu.j$P(`b`{-?u=#x!@~K');
define('NONCE_KEY',        ')[yux9Wxym8pnU4(j_<O(RxZwgauos6[IhGFtGc~mzg6R%QVpW +4L)MCI5czQ{|');
define('AUTH_SALT',        'vztO$L]oqF{$U-.VP%mb6S|BP.aEYeQWh@Yood;b&pvmcacDaVcU-qSbS>uJGj|>');
define('SECURE_AUTH_SALT', 'Bp186[ZqKzK>c;s8OY@XRlP{O(LRbqGZBJhrGl~gLfDt?-f6P}rZ~Pg:9%^G^!5V');
define('LOGGED_IN_SALT',   'G19~=vLw3k>#iFlo]rqZT_]Wv#2s<@X9(#z@28?d,e:4HLD)1E<.@MS6y>}vZE<*');
define('NONCE_SALT',       'zIitQ_G8r]^X 6{CM/3+2B1CM(Uf)V5#2~#M%L;~R~s4`:(-y5kj|PGL0Q->Pss&');

$table_prefix = 'wp_';

define( 'WP_DEBUG', false );

if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

require_once ABSPATH . 'wp-settings.php';
