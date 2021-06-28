<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', '$WORDPRESS_DB_USER' );

/** MySQL database password */
define( 'DB_PASSWORD', 'root' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', 'utf8_general_ci' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         'arq8GGK1BiND|v3BI.XLtXl{!q+%$W57B8tvtTheDyi#51xbQooL^$-f7!{g|[<+' );
define( 'SECURE_AUTH_KEY',  'z+tLZG|bJ-|R;dt,-gL~yIM noW_WqqkJ8i_v623w4h7:t:N+)CG5u?rjX?sW-2_' );
define( 'LOGGED_IN_KEY',    '|!1YW5xRr(2581!`7Ssfo7k}FDFPIu]4RYbk@YFIDAx QyrJ@@y*j=w@u^SJu0 E' );
define( 'NONCE_KEY',        'D]a^hTe5+`FihLuagwDeymkM RR}j4&<n2.v`->4qmx=8gl0xkD^z5OZ~{:|}u,B' );
define( 'AUTH_SALT',        'I2^dE-X~tahcpyzKt8-Ous>S96SK *V~}3R)`NyWlvFFeozfNfC9k)-uYg84AD`.' );
define( 'SECURE_AUTH_SALT', '4$#H1l4`I63<#ah`:6qHGyB~ekg(&6}$9f0[Y~YU{|%~G&G 5o@dcdlv|a:=s]X6' );
define( 'LOGGED_IN_SALT',   'B,}#:pCKFtq`&+/*`m+ilV9>xE-a+-T~t7+z2E5&cTe-U[N-+hT<W>h3X:Uw#e{2' );
define( 'NONCE_SALT',       'PSKw5v=l/8]U0^2lub:kQt3$-PD2+qbX9l:Jij@WPV;@koq KUFAh#6j:WfC9`^i' );

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
